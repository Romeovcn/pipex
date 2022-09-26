/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 22:22:40 by rvincent          #+#    #+#             */
/*   Updated: 2022/09/26 22:26:59 by rvincent         ###   ########.fr       */
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

int	get_first_cmd_index(char **argv)
{
	int	i;

	i = 2;
	if (ft_strmatch(argv[1], "here_doc"))
		i = 3;
	return (i);
}

void	get_fds(t_data *data, char **argv, int argc)
{
	if (ft_strmatch(argv[1], "here_doc"))
	{
		(*data).in_fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0666);
		(*data).out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_APPEND,
				0644);
	}
	else
	{
		(*data).in_fd = open(argv[1], O_RDONLY);
		(*data).out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	check_fds_error(*data, argc, argv);
}

void	get_here_doc(t_data data, char *sep)
{
	char	*line;
	int		fd;
	char	*sepator;

	sepator = ft_strjoin(sep, "\n");
	if (sepator == NULL)
		exit(1);
	fd = 0;
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(fd);
		if (ft_strmatch(line, sepator) || !line)
		{
			free(line);
			break ;
		}
		write(data.in_fd, line, ft_strlen(line));
		free(line);
	}
	free(sepator);
	close(data.in_fd);
	data.in_fd = open(".here_doc", O_RDONLY);
}
