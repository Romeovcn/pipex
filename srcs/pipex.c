/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:48:41 by rvincent          #+#    #+#             */
/*   Updated: 2022/08/30 20:31:34 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_data data, char **argv, char **envp)
{
	char test[] = "salut";
	if (ft_strlen(argv[2]) == 0)
	{
		//printf("wesh");
		//write(data.pipe_fd[1], test, 6);
		//dup2(data.pipe_fd[1], data.infile_fd);
		close(data.pipe_fd[0]);
		close(data.pipe_fd[1]);
		exit(1);
	} 
	data.options = ft_split(argv[2], ' ');
	data.correct_path = get_correct_path(data);
	dup2(data.pipe_fd[1], 1);
	dup2(data.infile_fd, 0);
	close(data.pipe_fd[0]);
	close(data.pipe_fd[1]);
	execve(data.correct_path, data.options, envp);
	exit(1);
}

void	second_child(t_data data, char **argv, char **envp)
{
	data.options = ft_split(argv[3], ' ');
	data.correct_path = get_correct_path(data);
	dup2(data.pipe_fd[0], 0);
	//dup2(data.outfile_fd, 1);
	close(data.pipe_fd[0]);
	close(data.pipe_fd[1]);
	execve(data.correct_path, data.options, envp);
	exit(1);
}

void	get_fds(t_data *data, char **argv)
{
	(*data).infile_fd = open(argv[1], O_RDONLY);
	(*data).outfile_fd = open(argv[4], O_WRONLY);
	check_fds_error(*data, argv);
	if (pipe((*data).pipe_fd) == -1)
	{
		close((*data).infile_fd);
		close((*data).outfile_fd);
		free_string_array((*data).paths);
		ft_printf("Couldn't open pipe.\n");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char buffer[1000];
	
	if (argc != 5)
	{
		ft_printf("Argument(s) missing or too much arguments\n");
		exit(1);
	}
	data.paths = get_paths(envp);
	get_fds(&data, argv);
	data.pid_1 = fork();
	if (data.pid_1 == -1)
		return (1);
	if (data.pid_1 == 0)
		first_child(data, argv, envp);
	waitpid(data.pid_1, &data.status, 0);
	manage_response_status(data, data.status);
	data.pid_2 = fork();
	if (data.pid_2 == -1)
		return (1);
	if (data.pid_2 == 0)
		second_child(data, argv, envp);

	//ft_bzero(buffer, 1000);
	//print_pipe_out(data);
	//read(data.pipe_fd[0], buffer, 1000);
	//printf("%s", buffer);
	close_fds(data);
	waitpid(data.pid_2, &data.status, 0);
	manage_response_status(data, data.status);
	free_string_array(data.paths);
}
