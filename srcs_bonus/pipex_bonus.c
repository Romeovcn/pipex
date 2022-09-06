/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:48:41 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/06 19:56:06 by rvincent         ###   ########.fr       */
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

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		pipe_fd[2];
	char 	buffer[1000];

	if (argc < 5)
	{
		ft_putstr_fd("Argument(s) missing.\n", 2);
		exit(1);
	}
	get_fds(&data, argv, argc);
	data.paths = get_paths(envp);
	pipe(pipe_fd);
	data.pid_1 = fork();
	if (data.pid_1 == -1)
		return (1);
	if (data.pid_1 == 0)
	{
		char *options[2] = {"cat", NULL};
		dup2(data.infile_fd, 0);
		dup2(pipe_fd[1], 1);
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		execve("/bin/cat", options, envp);
		exit(1);
	}
	waitpid(data.pid_1, &data.status, 0);
	data.pid_2 = fork();
	if (data.pid_2 == -1)
		return (1);
	if (data.pid_2 == 0)
	{
		char *options[3] = {"tail", "-n1", NULL};
		// dup2(data.infile_fd, 0);
		// dup2(pipe_fd[1], 1);
		dup2(pipe_fd[0], 0);
		close(pipe_fd[0]);
		// read(pipe_fd[0], buffer, 1000);
		// printf("%s\n", buffer);
		close(pipe_fd[1]);
		execve("/bin/tail", options, envp);
		exit(0);
	}
	// read(pipe_fd[0], buffer, 1000);
	// printf("%s\n", buffer);
	// int i = 3;
	// while (i < argc - 2)
	// {
	// 	pipe(pipe_fd);
	// 	data.pid_1 = fork();
	// 	if (data.pid_1 == 0)
	// 	{
	// 		read(pipe_fd[0], buffer, 1000);
	// 		printf("PIPE=%s\n", buffer);
	// 		printf("IM CHILD %s\n", argv[i]);
	// 		close(pipe_fd[0]);
	// 		close(pipe_fd[1]);
	// 		exit(0);
	// 	}
	// 	i++;
	// }

	close(pipe_fd[0]);
	close(pipe_fd[1]);
	waitpid(data.pid_2, &data.status, 0);
	printf("IM THE parent\n");
	exit(0);

	//waitpid(data.pid_1, &data.status, 0);
	//manage_response_status(data, data.status);
	//data.pid_2 = fork();
	//if (data.pid_2 == -1)
	//	return (1);
	//if (data.pid_2 == 0)
	//	second_child(data, argv, envp);
	//close_fds(data);
	//waitpid(data.pid_2, &data.status, 0);
	//manage_response_status(data, data.status);
	//free_string_array(data.paths);
	//exit(WEXITSTATUS(data.status));
}
