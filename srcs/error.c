/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:57:10 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/26 22:13:49 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	manage_response_status(t_data data, char *command_line)
{
	char	**command;

	command = ft_split(command_line, ' ');
	if (!command[0])
		ft_putstr_fd("Command not found : \n", 2);
	else if (WEXITSTATUS(data.status) == 127 && ft_strchr(command[0], '/'))
	{
		ft_putstr_fd("No such file or directory : ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd("\n", 2);
	}
	else if (WEXITSTATUS(data.status) == 127)
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd("\n", 2);
	}
	else if (WEXITSTATUS(data.status) == 126)
	{
		ft_putstr_fd("Permission denied : ", 2);
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd("\n", 2);
	}
	free_string_array(command);
}

void	check_fds_error(t_data data, char **argv)
{
	if (data.in_fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
	}
	if (data.out_fd == -1)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(argv[4], 2);
		ft_putstr_fd("\n", 2);
	}
}

void	check_fork_error(pid_t pid, t_data data)
{
	if (pid == -1)
	{
		ft_putstr_fd("Fork failed.\n", 2);
		close_fds(data);
		free_string_array(data.paths);
		exit(1);
	}
}
