# include "pipex.h"

void pipex()
{

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

int main(int argc, char **argv, char **envp)
{
    char *options[3] = {"ls", "-la", NULL};
    (void)argc;
    (void)argv;
    char **paths;
    int i = 0;
    int j = 0;

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
    while (paths[j])
    {
        paths[j] = get_command_path(paths[j], options[0]);
        // printf("PATH=%s ACCES=%d\n", paths[j], access(paths[j], F_OK | X_OK));
        if (access(paths[j], F_OK | X_OK) == 0)
            execve(paths[j], options, envp);
        free(paths[j]);
        j++;
    }
    free(paths);
    return (0);
}