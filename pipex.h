/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:52:17 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/12 23:43:55 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_data
{
	pid_t	pid_1;
	pid_t	pid_2;

	int		status;

	int		pipe_fd[2];

	int		in_fd;
	int		out_fd;

	char	**paths;
	char	*correct_path;

	char	**options;
}			t_data;

char		**get_paths(char **envp);
char		*get_command_path(char *path, char *command);
char		*get_correct_path(t_data data);

void		free_string_array(char **array);
void		close_fds(t_data data);

void		manage_response_status(t_data data, char *command);
void		check_fds_error(t_data data, char **argv);

#endif