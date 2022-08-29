/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:57:10 by rvincent          #+#    #+#             */
/*   Updated: 2022/08/29 15:57:11 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	manage_response_status(t_data data, int status)
{
	if (WEXITSTATUS(status) != 0)
	{
		free_string_array(data.paths);
		exit(1);
	}
}
