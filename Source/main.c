/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:33:43 by pooneh            #+#    #+#             */
/*   Updated: 2022/10/05 13:48:40 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/pipex.h"

void	set_data_general_case(t_pipex *data)
{
	int		i;

	i = 0;
	alloc_mem(data);
	while (i < data->num_of_processes)
	{
		data->copt[i] = command_options(data->argv[i + 2]);
		data->path[i] = path_of_command(data->copt[i][0], data->envp);
		i++;
	}
	data->path[i] = NULL;
	data->copt[i] = NULL;
}

/*here we check if it is heredoc case or a normal pipe case 
and we set up the whole data and paths*/

void	set_data_check_input(t_pipex *data, char **argv, char **envp, int argc)
{
	if (argc < 5)
	{
		perror("not enough arguments");
		exit(EXIT_FAILURE);
	}
	data->hd = 0;
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		here_doc_processing(data);
	if (!data->hd)
	{
		data->num_of_processes = argc - 3;
		set_data_general_case(data);
		open_files(data);
	}
}

/*this redirects the child to the related pipe and executes the command.
if the execution does not happen, it means that the command or command path are not valid
so we will publish an error with the error execution func. 
In this function, the program will exit with the command being mentioned as invalid in the error message
this is a bash behavior
Also, bash acts like this: when one child has invalid command/path, other children wont stop. 
all of them work in parallel and at the end the end the defect child process will produce the error.
thats why I put the error fuc there*/

void	child_redirection(t_pipex *data, int fd[MAX_FD][2], int i)
{
	if (i != 1)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i == data->num_of_processes)
		dup2(data->fd_out, STDOUT_FILENO);
	else
		dup2(fd[i][1], STDOUT_FILENO);
	close_fds(fd, *data);
	execve(data->path[i - 1], data->copt[i - 1], data->envp);
	error_execution(data, i - 1);
}

/*the parent is responsible to make childs and pipes and set the STDIN and STDOUT to the 
related in/out files
additionally it adds the data and when the processes are done it waits, frees everything and closes every file descriptior
so whatever happens in child proocesses, the parent will always free and exit*/

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		fd[MAX_FD][2];
	t_pipex	data;
	int		pid[MAX_FD];

	set_data_check_input(&data, argv, envp, argc);
	piping(&data, fd);
	dup2(data.fd_in, STDIN_FILENO);
	i = 1;
	while (i <= data.num_of_processes)
	{
		pid[i - 1] = fork();
		check_for_success(pid[i - 1]);
		if (!pid[i - 1])
			child_redirection(&data, fd, i);
		i++;
	}
	close_fds(fd, data);
	wait_for_children(pid, data);
	free_stuff(&data);
}
