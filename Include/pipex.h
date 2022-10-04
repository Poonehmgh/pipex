/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 20:01:08 by pmoghadd          #+#    #+#             */
/*   Updated: 2022/10/03 17:23:47 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/wait.h>
# include "../libft/libft.h"

# define MAX_FD 1023
typedef struct pipex
{
    char **path;
    char    ***copt;
    int     *item;
    int     argc;
    char    **argv;
    char    **envp;
    int     fd_in;
    int     fd_out;
    char    **hdcmnd1;
    char    **hdcmnd2;
    char    *hddelimiter;
    int     hd;
    int     num_of_processes;
} t_pipex;

/*   paths   */

char	**path_extract(char **envp);
char	*path_of_command(char *cmnd, char **envp);
char	**command_options(char *cmnd);

/*  here_doc    */
void    run_here_doc(t_pipex *data);
void	here_doc_processing(t_pipex *data, char **argv, int argc, char **envp);


/*  utils   */

void	open_files(t_pipex *data);
void	close_fds(int	fd[MAX_FD][2], t_pipex data);
void	wait_for_children(int *pid, t_pipex data);
void	check_for_success(int n);
void piping(t_pipex *data, int fd[MAX_FD][2]);

void	free_2d(char **a);
void	free_stuff(t_pipex *data);

void	error_execution(t_pipex *data, int i);
void	general_error(char *msg);




#endif