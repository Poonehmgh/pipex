/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 10:33:43 by pooneh            #+#    #+#             */
/*   Updated: 2022/09/29 14:35:00 by pooneh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Include/pipex.h"

//third main for the bonus arrangement// 

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



// int main(int argc, char **argv, char **envp)
// {
    
// 	int	i;
//     int fdo[2];
//     file_desc   *fd;
//     file_desc   *head;
// 	t_pipex	data;
//     int pid[argc];
//     char	*file1;
// 	// char	*file2;
// 	int		fd_in;

// 	i = 2;
//     pipe(fdo);
// 	set_data(&data, argc, argv, envp);
// 	file1 = data.argv[1];
//     fd_in = open(file1, O_RDONLY);
    
//     dup2(fd_in, STDIN_FILENO);
// 	pid[0] = fork();
//     dup2(fdo[1], STDIN_FILENO); //why not fd in ? check later
//     while (i < 5)
//     {

//         printf("this 1 %d i %d \n", pid[i - 2], i);
//         if (!pid[i - 2])
//         {
//             printf("this 2 %d with this i %d\n", pid[i - 2], i);
//             pid[i - 1] = fork();
//             if (!pid[i - 1])
//                 redirection(&data, fdo, i - 2);
//         }
//         waitpid(0, NULL, 0);
//         waitpid(pid[i - 1], NULL, 0);
//         i++;
//     }
//     close(fdo[0]);
//     close(fdo[1]);
//     waitpid(pid[i - 1], NULL, 0);
// }

// int main(int argc, char **argv, char **envp)
// {
//     int	i;
//     int fd[3][2];
// 	t_pipex	data;
//     int pid[argc];
//     char	*file1;
// 	int		fd_in;

// 	i = 0;
//     while (i < 3)
//     {
//         if (pipe(fd[i]) < 0)
// 			return(0);
// 		i++;
//     }
//     set_data(&data, argc, argv, envp);
// 	file1 = data.argv[1];
//     fd_in = open(file1, O_RDONLY);
// 	char *file2 = argv[argc - 1];
// 	int fd_out = open(file2, O_WRONLY);
//     dup2(fd_in, 0);
// 	dup2(fd_out, 1);
//     int pid1= fork();
//     if (pid1 == 0)
//     {
// 		i = 0;
// 		close(fd[1][0]);
// 		close(fd[0][1]);
// 		close(fd[2][0]);
// 		close(fd[2][1]);
//         dup2(fd[1][1], STDOUT_FILENO);
//         close(fd[0][0]);
//         close(fd[1][1]);
// 			// return 0;
// 		execve(data.path[i], data.copt[i], data.envp);
// 		printf("first child path %s cmnc %s i %d \n", data.path[i], data.copt[i][1], i);
		
		
//     }
// 	int pid2 = fork();
// 	if(pid2 == 0)
// 	{
// 		i = 1;
// 		close(fd[0][0]);
// 		close(fd[0][1]);
// 		close(fd[2][0]);
// 		close(fd[1][1]);
// 		dup2(fd[1][0], 0);
// 		dup2(fd[2][1], 1);
// 		close(fd[1][0]);
// 		close(fd[2][1]);
// 		// printf("second child path %s cmnc %s i %d \n", data.path[i], data.copt[i][1], i);
// 		execve(data.path[i], data.copt[i], data.envp);
// 		return(0);
// 	}
// 	int pid3 = fork();
// 	if (pid3 == 0)
// 	{
// 		close(fd[0][1]);
// 		close(fd[0][0]);
// 		close(fd[1][0]);
// 		close(fd[1][1]);
// 		close(fd[2][1]);
// 		i = 2;
// 		dup2(fd[2][0], STDIN_FILENO);
// 		close(fd[2][0]);
// 		execve(data.path[i], data.copt[i], data.envp);		
// 	}
// 			// printf("parent i %d \n", i);
// 	close(fd[0][1]);
// 	// close(fd_out);
// 	close(fd[0][0]);
// 	close(fd[1][0]);
// 	close(fd[1][1]);
// 	close(fd[2][0]);
// 	close(fd[2][1]);
// 	waitpid(pid1, NULL, 0);
// 	waitpid(pid2, NULL, 0);
// 	waitpid(pid3, NULL, 0);
// }

void	open_files(t_pipex *data)
{
	char *file1;
	char *file2; 
	
	file1 = data->argv[1];
    data->fd_in = open(file1, O_RDONLY);
	file2 = data->argv[data->argc - 1];
	data->fd_out = open(file2, O_WRONLY);
}
void	close_fds(int	fd[MAX_FD][2], t_pipex data)
{
	int i;

	i = 0;
	while (i < data.argc - 3)
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
	while (i < data.argc - 2)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
}

// void	run_here_doc(t_pipex *data)
// {
	
// }

void    run_here_doc(t_pipex *data)
{
    char    *buf;
    int     tmp;

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
    printf("sssss %d", data->fd_in);
    dup2(data->fd_in, STDIN_FILENO);
}

void	here_doc_processing(t_pipex *data, char **argv, int argc, char **envp)
{
    int i;

    i = 0;
    data->copt = (char ***)malloc(sizeof(char **) * (argc + 1));
	data->copt[0] = ft_split(argv[3], ' ');
	data->copt[1] = ft_split(argv[4], ' ');
    data->path = (char **)malloc(sizeof(char *) * 3);
    data->path[0] = path_of_command(data->copt[0][0], envp);
    data->path[1] = path_of_command(data->copt[1][0], envp);
	data->fd_out = open(argv[5], O_WRONLY);
    data->argv = argv;
	if (data->fd_out < 0)
	{
		perror("Error! Invalid file!\n");
		exit(0);
	}
    run_here_doc(data);

}

int main(int argc, char **argv, char **envp)
{
	int	i;
    int fd[MAX_FD][2];
	t_pipex	data;
    int pid[MAX_FD];
	
	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
		here_doc_processing(&data, argv, argc, envp);
	if (argc < 5)
	{
		ft_printf("Error! Not enough arguments!");
		exit(0);
	}
	i = 0;
    while (i < argc - 3)
    {
        if (pipe(fd[i]) < 0)
			return(2);
		i++;
    }
	set_data(&data, argc, argv, envp);
	open_files(&data);
	dup2(data.fd_in, STDIN_FILENO);
	dup2(data.fd_out, STDOUT_FILENO);
	i = 1;
	while ( i <= argc - 3)
	{
		pid[i - 1] = fork();
		if (!pid[i - 1])
		{	
			if (i != 1)
				dup2(fd[i - 1][0], STDIN_FILENO);
			dup2(fd[i][1], STDOUT_FILENO);
			close_fds(fd, data);
			execve(data.path[i - 1], data.copt[i - 1], data.envp);
			perror("Error while executing!\n");
			exit(2);
		}
		if (pid[i - 1] < 0)
		{
			perror("Error! Fork unsuccessful!\n");
			exit(2);
		}
		i++;
	}
	close_fds(fd, data);
	wait_for_children(pid, data);
}
// now it works. to do: make a func and suitable structre for pipes and its closing and freeing !
// error management
// heredoc
// some more tests
//problem: when I allocate memory for the fds, it doesnt work. when it is defined as local var array in main, it works. why
/////////
// 2nd backup

// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   main2.c                                            :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: pooneh <pooneh@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/09/21 10:33:43 by pooneh            #+#    #+#             */
// /*   Updated: 2022/09/29 14:07:31 by pooneh           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "../Include/pipex.h"

// //third main for the bonus arrangement// 

// void	set_data(t_pipex *data, int argc, char **argv, char **envp)
// {
// 	int		i;

// 	i = 0;
// 	data->argc = argc;
// 	data->argv = argv;
// 	data->envp = envp;
// 	data->copt = (char ***)malloc(sizeof(char **) * (argc + 1));
// 	data->path = (char **)malloc(sizeof(char *) * (argc + 1)); // check and free
// 	while (i < argc - 3)
// 	{
// 		data->copt[i] = command_options(argv[i + 2]);
// 		data->path[i] = path_of_command(data->copt[i][0], envp);
// 		if (!data->path[i])
// 		{
// 			perror("\nError! Command does not exist!\n");
// 			exit(2);
// 		}
			
// 		// printf("i: %d	path: %s copt 1: %s	\n", i, data->path[i], data->copt[i][1]);
// 		i++;
// 	}
// }

// void	open_files(t_pipex *data)
// {
// 	char *file1;
// 	char *file2; 
	
// 	file1 = data->argv[1];
//     data->fd_in = open(file1, O_RDONLY);
// 	file2 = data->argv[data->argc - 1];
// 	data->fd_out = open(file2, O_WRONLY);
// }
// void	close_fds(int	fd[MAX_FD][2], t_pipex data)
// {
// 	int i;

// 	i = 0;
// 	while (i < data.num_of_processes)
// 	{
// 		close(fd[i][0]);
// 		close(fd[i][1]);
// 		i++;
// 	}
// }
// void	wait_for_children(int *pid, t_pipex data)
// {
// 	int	i;

// 	i = 0;
// 	while (i < data.num_of_processes + 1)
// 	{
// 		waitpid(pid[i], NULL, 0);
// 		i++;
// 	}
// }

// void    run_here_doc(t_pipex *data)
// {
//     char    *buf;
//     int     tmp;

//     tmp = open(".hd", O_TRUNC | O_CREAT | O_WRONLY, 0000644);
// 	while (1)
// 	{
// 		write(1, "heredoc> ", 9);
// 		buf = get_next_line(STDIN_FILENO);
// 		if (ft_strncmp(data->argv[2], buf, ft_strlen(data->argv[2])) == 0)
// 			break ;
//         ft_putstr_fd(buf, tmp);
// 		free(buf);
// 	}
// 	free(buf);
// 	close(tmp);
//     data->fd_in = open(".hd", O_RDONLY);
//     dup2(data->fd_in, STDIN_FILENO);
// }

// void	here_doc_processing(t_pipex *data, char **argv, int argc, char **envp)
// {
//     int i;

//     i = 0;
//     data->copt = (char ***)malloc(sizeof(char **) * (argc + 1));
// 	data->copt[0] = ft_split(argv[3], ' ');
// 	data->copt[1] = ft_split(argv[4], ' ');
// 	data->copt[2] = NULL;
//     data->path = (char **)malloc(sizeof(char *) * 3);
//     data->path[0] = path_of_command(data->copt[0][0], envp);
//     data->path[1] = path_of_command(data->copt[1][0], envp);
// 	data->path[2] = NULL;
// 	if (!data->path[0] || !data->path[1])
// 	{
// 		perror("\nError! Command does not exist!\n");
// 		exit(2);
// 	}
// 	data->fd_out = open(argv[5], O_WRONLY);
//     data->argv = argv;
// 	if (data->fd_out < 0)
// 	{
// 		perror("Error! Invalid file!\n");
// 		exit(0);
// 	}
// 	data->hd = 1;
// 	data->num_of_processes = argc - 4;
//     run_here_doc(data);
// }

// int main(int argc, char **argv, char **envp)
// {
// 	int	i;
//     int fd[MAX_FD][2];
// 	t_pipex	data;
//     int pid[MAX_FD];
	
// 	data.hd = 0;
// 	if (!ft_strncmp(argv[1], "here_doc", ft_strlen(argv[1])))
// 		here_doc_processing(&data, argv, argc, envp);
// 	if (argc < 5)
// 	{
// 		ft_printf("Error! Not enough arguments!");
// 		exit(0);
// 	}
// 	if (!data.hd)
// 	{
// 		set_data(&data, argc, argv, envp);
// 	printf("data pro %d path %s \n", data.num_of_processes, data.path[0]);	
// 		open_files(&data);
// 		data.num_of_processes = argc - 3;
// 	}
// 	i = 0;
//     while (i < data.num_of_processes)
//     {
//         if (pipe(fd[i]) < 0)
// 			return(2);
// 		i++;
//     }
// 	dup2(data.fd_in, STDIN_FILENO);
// 	dup2(data.fd_out, STDOUT_FILENO);
// 	i = 1;
// 	while ( i <= data.num_of_processes)
// 	{
// 		pid[i - 1] = fork();
// 		if (pid[i - 1] < 0)
// 		{
// 			perror("Error! Fork unsuccessful!\n");
// 			exit(2);
// 		}
// 		if (!pid[i - 1])
// 		{	
// 			if (i != 1)
// 				dup2(fd[i - 1][0], STDIN_FILENO);
// 			dup2(fd[i][1], STDOUT_FILENO);
// 			close_fds(fd, data);
// 			execve(data.path[i - 1], data.copt[i - 1], data.envp);
// 			perror("Error while executing! ");
// 			exit(2);
// 		}
// 		i++;
// 	}
// 	close_fds(fd, data);
// 	wait_for_children(pid, data);
// }
// now it works. to do: make a func and suitable structre for pipes and its closing and freeing !
// error management
// heredoc
// some more tests
//problem: when I allocate memory for the fds, it doesnt work. when it is defined as local var array in main, it works. why


//heredoc redirection doesnt work
// normineeeteeee
// error ? 
// testers ?!
//leaks