/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:15:11 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/09/29 18:46:22 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../Include/pipex.h"

char	**path_extract(char **envp)
{
	char	**paths;
	int		i;
	char	**tmp;

	i = 0;
	paths = ft_split(envp[4], ':');
	while (paths[i])
	{
		paths[i] = ft_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}

char	*path_of_command(char *cmnd, char **envp)
{
	char	**s;	
	char	*a;
	int		i;

	i = 0;
	s = path_extract(envp);
	while (s[i])
	{
		a = ft_strjoin(s[i], cmnd);
		free(s[i]);
		if (!access(a, F_OK))
		{
			return (a);
		}
		free(a);
		i++;
	}
	return (NULL);
}

char	**command_options(char *cmnd)
{
	char	**copt;

	copt = ft_split(cmnd, ' ');
	return (copt);
}
