/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:48:48 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/26 22:27:08 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_pipes(t_data data)
{
	close(data.pipe_fd[0]);
	close(data.pipe_fd[1]);
}

void	close_files(t_data data)
{
	if (data.in_fd != -1)
		close(data.in_fd);
	if (data.out_fd != -1)
		close(data.out_fd);
}

void	close_fds(t_data data)
{
	close_pipes(data);
	close_files(data);
}

void	free_and_exit_child(t_data data)
{
	close_fds(data);
	free_string_array(data.paths);
	exit(1);
}

void	pipe_error(t_data data)
{
	close_files(data);
	free_string_array(data.paths);
	exit(1);
}
