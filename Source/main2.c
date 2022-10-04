/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:33:43 by pooneh            #+#    #+#             */
/*   Updated: 2022/10/04 15:51:16 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/pipex.h"

void	set_data(t_pipex *data, int argc, char **argv, char **envp)
{
	int		i;

	i = 0;
	data->argc = argc;
	data->argv = argv;
	data->envp = envp;
	data->copt = (char ***)malloc(sizeof(char **) * (argc + 1));
	data->path = (char **)malloc(sizeof(char *) * (argc + 1)); // check and free
	while (i < data->num_of_processes)
	{
		data->copt[i] = command_options(argv[i + 2]);
		data->path[i] = path_of_command(data->copt[i][0], envp);
		if (!data->path[i])
		{
			perror("\nError! command not found ");
			exit(EXIT_FAILURE);
		}	
		i++;
	}
	data->path[i] = NULL;
	data->copt[i] = NULL;
}

void	set_data_check_input(t_pipex *data, char **argv, char **envp, int argc)
{
	data->hd = 0;

	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		here_doc_processing(data, argv, argc, envp);
	if (!data->hd)
	{
		if (argc < 5)
		{
			perror("not enough arguments");
			exit(EXIT_FAILURE);
		}
		data->num_of_processes = argc - 3;
		set_data(data, argc, argv, envp);
		open_files(data);
	}
}

void	child_redirection(t_pipex *data, int fd[MAX_FD][2], int i)
{
	if (i != 1)
		dup2(fd[i - 1][0], STDIN_FILENO);
	if (i == data->num_of_processes)
		dup2(data->fd_out, STDOUT_FILENO);
	else
		dup2(fd[i][1], STDOUT_FILENO);
	close_fds(fd, *data);
	// write(data->fd_out, data->path[i - 1], ft_strlen(data->path[i - 1]));
	// write(data->fd_out, "\n",1);

	execve(data->path[i - 1], data->copt[i - 1], data->envp);
	// error_execution(data, i - 1);
}

void	free_2d(char **a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		free(a[i]);
		i++;
	}
	free(a);
}

void	free_stuff(t_pipex *data)
{
	int	i;

	i = 0;
	while (data->path[i])
	{
		free_2d(data->copt[i]);
		free(data->path[i]);
		i++;
	}
	free(data->path);
	free(data->copt);
}

int	main(int argc, char **argv, char **envp)
{
	int		i;
	int		fd[MAX_FD][2];
	t_pipex	data;
	int		pid[MAX_FD];

	set_data_check_input(&data, argv, envp, argc);
	piping(&data, fd);
	dup2(data.fd_in, STDIN_FILENO);
	// dup2(data.fd_out, STDOUT_FILENO);
	i = 1;
	while (i <= data.num_of_processes)
	{
		pid[i - 1] = fork();
		check_for_success(pid[i - 1]);
		if (!pid[i - 1])
	{
		// printf("hhhhhhhho;qslk  %d", i);
			child_redirection(&data, fd, i);}
		i++;
	}
	close_fds(fd, data);
	free_stuff(&data);
	wait_for_children(pid, data);
}

//hd redirection
//commands with paths
//bash implementation