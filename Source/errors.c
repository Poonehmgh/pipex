/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 14:33:02 by pooneh            #+#    #+#             */
/*   Updated: 2022/10/05 12:46:06 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../Include/pipex.h"

void	error_execution(t_pipex *data, int i)
{
	write(2, data->copt[i][0], ft_strlen(data->copt[i][0]));
	write(2, ": command not found", 19);
	exit(EXIT_FAILURE);
}

void	general_error(char *msg)
{
	perror(msg);
	exit(EXIT_FAILURE);
}
