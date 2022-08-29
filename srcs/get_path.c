# include "pipex.h"

char **get_paths(char **envp)
{
    int i;
    char **paths;

    i = 0;
    while (envp[i])
    {
        if (envp[i][0] == 'P' && envp[i][1] == 'A' && envp[i][2] == 'T' && envp[i][3] == 'H' && envp[i][4] == '=')
        {
            while (*envp[i] != '/')
                envp[i]++;
            paths = ft_split(envp[i], ':');
        }
        i++;
    }
    return (paths);
}

char    *get_command_path(char *path, char *command)
{
    char    *command_path;
    int     i;
    int     j;

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

char *get_correct_path(char **paths, char *command)
{
    char *correct_path;
    int j;

    correct_path = NULL;
    j = 0;
    while (paths[j])
    {
        paths[j] = get_command_path(paths[j], command);
        if (access(paths[j], F_OK | X_OK) == 0 && correct_path == NULL)
            correct_path = ft_strdup(paths[j]);
        free(paths[j]);
        j++;
    }
    free(paths);
	//if (correct_path == NULL)
	//{
	//	// only exit one fork !! Need fix
	//	ft_printf("Command doesn't exist.\n");
	//	exit(1);
	//}
    return (correct_path);
}