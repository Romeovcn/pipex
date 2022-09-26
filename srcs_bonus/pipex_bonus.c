/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:48:41 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/26 23:37:21 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	create_child_and_exec(t_data *data, char **argv, int i, char **envp)
{
	if (pipe(data->pipe_fd) == -1)
		pipe_error(*data);
	data->pid[i] = fork();
	if (data->pid[i] == -1)
		free_and_exit_child(*data);
	if (data->pid[i] == 0)
	{
		if ((data->in_fd == -1 && i == 2) || (data->out_fd == -1 && !argv[i
					+ 2]))
			free_and_exit_child(*data);
		data->options = ft_split(argv[i], ' ');
		if (data->options == NULL)
			exit(1);
		data->correct_path = get_correct_path(*data);
		if (argv[i + 2] == 0)
			dup2(data->out_fd, 1);
		else
			dup2(data->pipe_fd[1], 1);
		close_pipes(*data);
		execve(data->correct_path, data->options, envp);
		exit(1);
	}
	dup2(data->pipe_fd[0], 0);
	close_pipes(*data);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	if (argc < 5)
	{
		ft_putstr_fd("Argument(s) missing.\n", 2);
		exit(1);
	}
	get_fds(&data, argv, argc);
	if (ft_strmatch(argv[1], "here_doc"))
		get_here_doc(data, argv[2]);
	data.paths = get_paths(envp);
	dup2(data.in_fd, 0);
	i = get_first_cmd_index(argv);
	while (i < argc - 1)
		create_child_and_exec(&data, argv, i++, envp);
	i = get_first_cmd_index(argv);
	while (i < argc - 1 && waitpid(data.pid[i], &data.status, 0) > 0)
		manage_response_status(data, argv[i++]);
	if (ft_strmatch(argv[1], "here_doc"))
		unlink(".here_doc");
	free_string_array(data.paths);
	close_files(data);
	exit(WEXITSTATUS(data.status));
}
//valgrind --track-fds=yes
