/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/29 16:57:10 by pooneh            #+#    #+#             */
/*   Updated: 2022/10/05 12:46:31 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/pipex.h"

void	run_here_doc(t_pipex *data)
{
	char	*buf;
	int		tmp;

	data->tmpfile = ".hd";
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
}

void	here_doc_processing(t_pipex *data)
{
	int	i;

	i = 0;
	data->num_of_processes = data->argc - 4;
	alloc_mem(data);
	while (i < data->num_of_processes)
	{
		data->copt[i] = ft_split(data->argv[3 + i], ' ');
		data->path[i] = path_of_command(data->copt[i][0], data->envp);
		if (!data->path[i])
			general_error("command not found");
		i++;
	}
	data->copt[i] = NULL;
	data->path[i] = NULL;
	data->fd_out = open(data->argv[data->argc - 1],
			O_TRUNC | O_CREAT | O_WRONLY, 0000644);
	data->hd = 1;
	if (data->fd_out < 0)
		general_error("error while openning the file");
	run_here_doc(data);
}
