/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_exit_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:48:48 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/09 18:04:26 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	close(data.infile_fd);
	close(data.outfile_fd);
}
