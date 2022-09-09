/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:48:41 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/09 23:48:08 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int ft_strmatch(char *str1, char *str2)
{
	if (!str1 || !str2)
		return 0;
	while (*str1 && *str2 && *str1 == *str2)
	{
		str1++;
		str2++;
	}
	if (*str1 != 0 || *str2 != 0)
		return 0;
	return 1;
}

void	get_fds(t_data *data, char **argv, int argc)
{
	if (ft_strmatch(argv[1], "here_doc"))
		(*data).infile_fd = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0666);
	else
		(*data).infile_fd = open(argv[1], O_RDONLY);
	(*data).outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0666);
	//check_fds_error(*data, argv);
	//if (pipe((*data).pipe_fd) == -1)
	//{
	//	close((*data).infile_fd);
	//	close((*data).outfile_fd);
	//	free_string_array((*data).paths);
	//	ft_putstr_fd("Couldn't open pipe.\n", 2);
	//	exit(1);
	//}
}

void create_child_and_exec(t_data *data, char *command, int i, int argc, char **envp)
{
	pipe(data->pipe_fd);
	data->pid_1 = fork();
	if (data->pid_1 == -1)
		exit(1);
	if (data->pid_1 == 0)
	{
		data->options = ft_split(command, ' ');
		data->correct_path = get_correct_path(*data);
		if (i == argc - 2)
			dup2(data->outfile_fd, 1);
		else
			dup2(data->pipe_fd[1], 1);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		execve(data->correct_path, data->options, envp);
		exit(1);
	}
	dup2(data->pipe_fd[0], 0);
	close(data->pipe_fd[0]);
	close(data->pipe_fd[1]);
	waitpid(data->pid_1, &data->status, 0);
	manage_response_status(*data, data->status);
}

void get_here_doc(t_data data, char *sep)
{
	char *line;
	int fd;
	char *sepator = ft_strjoin(sep, "\n");

	fd = 0;
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(fd);
		if (ft_strmatch(line, sepator) || !line)
		{
			free(line);
			break ;
		}
		write(data.infile_fd, line, ft_strlen(line));
		free(line);
	}
	free(sepator);
	close(data.infile_fd);
	data.infile_fd = open("here_doc", O_RDONLY);
}


int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		pipe_fd[2];
	int 	i;
	char 	buffer[50];

	if (argc < 5)
	{
		ft_putstr_fd("Argument(s) missing.\n", 2);
		exit(1);
	}
	get_fds(&data, argv, argc);
	if (ft_strmatch(argv[1], "here_doc"))
		get_here_doc(data, argv[2]);
	data.paths = get_paths(envp);
	dup2(data.infile_fd, 0);
	
	//---------------------------------------------------------//
	//						While child						   //
	//---------------------------------------------------------//
	if (ft_strmatch(argv[1], "here_doc"))
		i = 3;
	else
		i = 2;
	while (i < argc - 1)
	{
		create_child_and_exec(&data, argv[i], i , argc, envp);
		i++;
	}
	//---------------------------------------------------------//
	//						Parent						  	   //
	//---------------------------------------------------------//
	close(data.pipe_fd[0]);
	unlink("here_doc");
	printf("IM THE parent\n");
	exit(0);
}
//valgrind --quiet --track-fds=yes
