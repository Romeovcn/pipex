/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:57:10 by rvincent          #+#    #+#             */
/*   Updated: 2022/08/31 22:20:01 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	manage_response_status(t_data data, int status)
{
	if (WEXITSTATUS(status) == 127)
		ft_putstr_fd("Command not found.\n", 2);
}

void	check_fds_error(t_data data, char **argv)
{
	if (data.infile_fd == -1)
	{
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	if (data.outfile_fd == -1)
	{
		if (data.infile_fd != -1)
			close(data.infile_fd);
		free_string_array(data.paths);
		ft_putstr_fd(argv[4], 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	if (data.infile_fd == -1)
	{
		free_string_array(data.paths);
		exit(0);
	}
}
