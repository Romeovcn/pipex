/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 14:52:17 by rvincent          #+#    #+#             */
/*   Updated: 2022/08/28 22:08:20 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <errno.h>
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
	int		status_2;

	int		pipe_fd[2];

	int		infile_fd;
	int		outfile_fd;

	char	**paths;
}			t_data;

char		**get_paths(char **envp);
char		*get_command_path(char *path, char *command);
char		*get_correct_path(char **paths, char *command);

#endif