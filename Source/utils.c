/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:58:45 by pooneh            #+#    #+#             */
/*   Updated: 2022/10/05 12:14:01 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/pipex.h"

void	open_files(t_pipex *data)
{
	char	*file1;
	char	*file2;

	file1 = data->argv[1];
	data->fd_in = open(file1, O_RDONLY);
	if (data->fd_in < 0)
		general_error("error while openning the file");
	file2 = data->argv[data->argc - 1];
	data->fd_out = open(file2, O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	if (data->fd_out < 0)
		general_error("error while openning the file");
}

void	close_fds(int fd[MAX_FD][2], t_pipex data)
{
	int	i;

	i = 0;
	while (i < data.num_of_processes)
	{
		close(fd[i][0]);
		close(fd[i][1]);
		i++;
	}
}

void	wait_for_children(int *pid, t_pipex data)
{
	int	i;

	i = 0;
	while (i < data.num_of_processes + 1)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

void	check_for_success(int n)
{
	if (n < 0)
	{
		perror("error! unsuccessfull forking");
		exit(EXIT_FAILURE);
	}
}

void	piping(t_pipex *data, int fd[MAX_FD][2])
{
	int	i;

	i = 0;
	while (i < data->num_of_processes)
	{
		if (pipe(fd[i]) < 0)
			general_error("error while openning the pipe");
		i++;
	}
}
