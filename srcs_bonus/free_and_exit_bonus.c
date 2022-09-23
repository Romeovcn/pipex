/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:48:48 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/23 22:47:06 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	free_string_array(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	if (array)
		free(array);
}

void	close_fds(t_data data)
{
	close(data.pipe_fd[0]);
	close(data.pipe_fd[1]);
	if (data.in_fd != -1)
		close(data.in_fd);
	if (data.out_fd != -1)
		close(data.out_fd);
}
