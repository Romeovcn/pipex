/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rvincent <rvincent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:48:45 by rvincent          #+#    #+#             */
/*   Updated: 2022/08/31 22:19:52 by rvincent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_paths(char **envp)
{
	int		i;
	char	**paths;

	i = 0;
	while (envp[i])
	{
		if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T'
			&& envp[i][3] == 'H' && envp[i][4] == '=')
		{
			while (*envp[i] && *envp[i] != '/')
				envp[i]++;
			paths = ft_split(envp[i], ':');
		}
		i++;
	}
	return (paths);
}

char	*get_command_path(char *path, char *command)
{
	char	*command_path;
	int		i;
	int		j;

	i = 0;
	j = 0;
	command_path = malloc(ft_strlen(path) + ft_strlen(command) + 2);
	while (path[i])
	{
		command_path[i] = path[i];
		i++;
	}
	command_path[i] = '/';
	i++;
	while (command[j])
	{
		command_path[i + j] = command[j];
		j++;
	}
	command_path[i + j] = 0;
	free(path);
	return (command_path);
}

char	*get_correct_path(t_data data)
{
	char	*correct_path;
	int		i;

	correct_path = NULL;
	i = 0;
	if (data.options[0] && access(data.options[0], F_OK | X_OK) == 0)
	{
		correct_path = ft_strdup(data.options[0]);
		free_string_array(data.paths);
		return (correct_path);
	}
	while (data.paths[i] && data.options[0])
	{
		data.paths[i] = get_command_path(data.paths[i], data.options[0]);
		if (access(data.paths[i], F_OK | X_OK) == 0 && correct_path == NULL)
			correct_path = ft_strdup(data.paths[i]);
		i++;
	}
	free_string_array(data.paths);
	if (correct_path == NULL)
	{
		free_string_array(data.options);
		exit(127);
	}
	return (correct_path);
}
