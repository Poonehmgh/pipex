/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:57:10 by pooneh            #+#    #+#             */
/*   Updated: 2022/09/30 14:13:15 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/pipex.h"

void	run_here_doc(t_pipex *data)
{
	char	*buf;
	int		tmp;

	tmp = open(".hd", O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	while (1)
	{
		write(1, "heredoc> ", 9);
		buf = get_next_line(STDIN_FILENO);
		if (ft_strncmp(data->argv[2], buf, ft_strlen(data->argv[2])) == 0)
			break ;
		ft_putstr_fd(buf, tmp);
		free(buf);
	}
	free(buf);
	close(tmp);
	data->fd_in = open(".hd", O_RDONLY);
	// dup2(data->fd_in, STDIN_FILENO);
}

void	here_doc_processing(t_pipex *data, char **argv, int argc, char **envp)
{
	int	i;

    i = 0;
	data->num_of_processes = argc - 4;
    data->copt = (char ***)malloc(sizeof(char **) * (argc + 1));
	data->path = (char **)malloc(sizeof(char *) * (argc + 1));
	while (i < data->num_of_processes)
	{
		data->copt[i] = ft_split(argv[3 + i], ' ');
		data->path[i] = path_of_command(data->copt[i][0], envp);
		if (!data->path[i])
		{
			perror("\nError! Command does not exist!\n");
			exit(2);
		}
		i++;
	}
	data->copt[i] = NULL;
	data->path[i] = NULL;
	data->fd_out = open(argv[argc - 1], O_WRONLY);
	data->argv = argv;
	if (data->fd_out < 0)
	{
		perror("Error! Invalid file!\n");
		exit(0);
	}
	data->hd = 1;
	run_here_doc(data);
}
