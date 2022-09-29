/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:33:43 by pooneh            #+#    #+#             */
/*   Updated: 2022/09/29 17:08:52 by pooneh           ###   ########.fr       */
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
	while (i < argc - 3)
	{
		data->copt[i] = command_options(argv[i + 2]);
		data->path[i] = path_of_command(data->copt[i][0], envp);
		if (!data->path[i])
		{
			perror("\nError! Command does not exist!\n");
			exit(2);
		}	
		// printf("i: %d	path: %s copt 1: %s	\n", i, data->path[i], data->copt[i][1]);
		i++;
	}
}

void	set_data_check_input(t_pipex *data, char **argv, char **envp, int argc)
{
	data->hd = 0;
	if (argc < 5)
	{
		ft_printf("Error! Not enough arguments!");
		exit(0);
	}
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		here_doc_processing(data, argv, argc, envp);
	if (!data->hd)
	{
		set_data(data, argc, argv, envp);
		open_files(data);
		data->num_of_processes = argc - 3;
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
	execve(data->path[i - 1], data->copt[i - 1], data->envp);
	perror("Error while executing! ");
	exit(2);
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
	dup2(data.fd_out, STDOUT_FILENO);
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
}
