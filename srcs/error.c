/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:57:10 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/14 22:39:16 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	manage_response_status(t_data data, char *command)
{
	if (WEXITSTATUS(data.status) == 127)
	{
		ft_putstr_fd("Command not found : ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd("\n", 2);
	}
}

void	check_fds_error(t_data data, char **argv)
{
	if (data.in_fd == -1)
	{
		if (data.out_fd != -1)
			close(data.out_fd);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd("\n", 2);
	}
	if (data.out_fd == -1)
	{
		if (data.in_fd != -1)
			close(data.in_fd);
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd(" : ", 2);
		ft_putstr_fd(argv[4], 2);
		ft_putstr_fd("\n", 2);
		exit(1);
	}
	if (data.in_fd == -1)
		exit(1);
}
