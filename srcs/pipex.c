/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:48:41 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/12 23:48:05 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	first_child(t_data *data, char **argv, char **envp)
{
	data->pid_1 = fork();
	if (data->pid_1 == -1)
		exit(1);
	if (data->pid_1 == 0)
	{
		data->options = ft_split(argv[2], ' ');
		data->correct_path = get_correct_path(*data);
		dup2(data->pipe_fd[1], 1);
		dup2(data->in_fd, 0);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		execve(data->correct_path, data->options, envp);
		exit(1);
	}
	waitpid(data->pid_1, &data->status, 0);
	manage_response_status(*data, argv[2]);
}

void	second_child(t_data *data, char **argv, char **envp)
{
	data->pid_2 = fork();
	if (data->pid_2 == -1)
		exit(1);
	if (data->pid_2 == 0)
	{
		data->options = ft_split(argv[3], ' ');
		data->correct_path = get_correct_path(*data);
		dup2(data->pipe_fd[0], 0);
		dup2(data->out_fd, 1);
		close(data->pipe_fd[0]);
		close(data->pipe_fd[1]);
		execve(data->correct_path, data->options, envp);
		exit(1);
	}
	close_fds(*data);
	waitpid(data->pid_2, &data->status, 0);
	manage_response_status(*data, argv[3]);
}

void	get_fds(t_data *data, char **argv)
{
	(*data).in_fd = open(argv[1], O_RDONLY);
	(*data).out_fd = open(argv[4], O_CREAT | O_RDWR | O_TRUNC, 0644);
	check_fds_error(*data, argv);
	if (pipe((*data).pipe_fd) == -1)
	{
		close((*data).in_fd);
		close((*data).out_fd);
		free_string_array((*data).paths);
		ft_putstr_fd("Couldn't open pipe.\n", 2);
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	if (argc != 5)
	{
		ft_putstr_fd("Argument(s) missing or too much arguments\n", 2);
		exit(1);
	}
	get_fds(&data, argv);
	data.paths = get_paths(envp);
	first_child(&data, argv, envp);
	second_child(&data, argv, envp);
	free_string_array(data.paths);
	exit(WEXITSTATUS(data.status));
}
