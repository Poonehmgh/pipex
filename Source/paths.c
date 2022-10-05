/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pmoghadd <pmoghadd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/17 16:15:11 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/10/05 11:36:40 by pmoghadd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"../Include/pipex.h"

char	*ppx_strjoin(char *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*dst;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	dst = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dst == NULL)
		return (NULL);
	while (s1[i])
	{
		dst[i] = s1[i];
		i++;
	}
	free(s1);
	while (s2[j])
	{		
		dst[i] = s2[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst);
}

char	**path_extract(char **envp)
{
	char	**paths;
	int		i;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	if (!envp[i])
		general_error("envp is not valid");
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i])
	{
		paths[i] = ppx_strjoin(paths[i], "/");
		i++;
	}
	return (paths);
}

char	*path_of_command(char *cmnd, char **envp)
{
	char	**s;	
	char	*a;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s = path_extract(envp);
	while (s[i])
	{
		a = ppx_strjoin(s[i], cmnd);
		if (!access(a, F_OK))
		{
			j = i;
			while (s[++j])
				free(s[j]);
			free(s);
			return (a);
		}
		free(a);
		i++;
	}
	free(s);
	return (NULL);
}

char	**command_options(char *cmnd)
{
	char	**copt;

	copt = ft_split(cmnd, ' ');
	return (copt);
}
