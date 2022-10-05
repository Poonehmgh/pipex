/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   freeing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 11:48:24 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/10/05 13:10:03 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Include/pipex.h"

void	alloc_mem(t_pipex	*data)
{
	data->copt = (char ***)malloc(sizeof(char **)
			* (data->num_of_processes + 1));
	if (!data->copt)
		return ;
	data->path = (char **)malloc(sizeof(char *) * (data->num_of_processes + 1));
	if (!data->path)
		return ;
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
	while (i < data->num_of_processes)
	{
		free_2d(data->copt[i]);
		if (data->path[i])
			free(data->path[i]);
		i++;
	}
	free(data->path);
	free(data->copt);
	if (data->hd)
		unlink(data->tmpfile);
}
