/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:48:41 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/09 18:06:59 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_data data, char **argv, char **envp)
{
	//data.options = ft_split(argv[2], ' ');
	//data.correct_path = get_correct_path(data);
	//dup2(data.pipe_fd[1], 1);
	write(data.pipe_fd[1], "Romeo", 6);
	//dup2(data.infile_fd, 0);
	close(data.pipe_fd[0]);
	close(data.pipe_fd[1]);
	//execve(data.correct_path, data.options, envp);
	//sleep(5);
	printf("Im the first child\n");
	exit(0);
}

void	second_child(t_data data, char **argv, char **envp)
{
	data.options = ft_split(argv[3], ' ');
	data.correct_path = get_correct_path(data);
	dup2(data.pipe_fd[0], 0);
	// dup2(data.outfile_fd, 1);
	close(data.pipe_fd[0]);
	close(data.pipe_fd[1]);
	execve(data.correct_path, data.options, envp);
	exit(1);
}

void	get_fds(t_data *data, char **argv, int argc)
{
	(*data).infile_fd = open(argv[1], O_RDONLY);
	(*data).outfile_fd = open(argv[argc - 1], O_WRONLY | O_CREAT, 0666);
	check_fds_error(*data, argv);
	//if (pipe((*data).pipe_fd) == -1)
	//{
	//	close((*data).infile_fd);
	//	close((*data).outfile_fd);
	//	free_string_array((*data).paths);
	//	ft_putstr_fd("Couldn't open pipe.\n", 2);
	//	exit(1);
	//}
}

//void close_pipe(int *pipe_in, int *pipe_out)
//{
//	close(pipe_in[1]);
//	close(pipe_in[0]);
//	close(pipe_out[1]);
//	close(pipe_out[0]);
//}

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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		pipe_fd[2];
	char 	buffer[50];

	if (argc < 5)
	{
		ft_putstr_fd("Argument(s) missing.\n", 2);
		exit(1);
	}
	get_fds(&data, argv, argc);
	data.paths = get_paths(envp);
	dup2(data.infile_fd, 0);
	
	//---------------------------------------------------------//
	//						While child						   //
	//---------------------------------------------------------//
	int i = 2;
	while (i < argc - 1)
	{
		//printf("%s\n", argv[i++]);
		create_child_and_exec(&data, argv[i], i , argc, envp);
		i++;
	}
	//---------------------------------------------------------//
	//						Parent						  	   //
	//---------------------------------------------------------//
	//read(pipe_fd[0], buffer, 50);
	//printf("%s", buffer);
	close(data.pipe_fd[0]);
	printf("IM THE parent\n");
	exit(0);
}
