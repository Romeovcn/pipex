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
    return (correct_path);
}

int main(int argc, char **argv, char **envp)
{
    (void)argc;
    (void)argv;

    char **paths;
    char *correct_path;
    // char *options[3] = {"ls", "-la", NULL};
    
    // pid_t pid;
    // int status;
    // int pipefd[2];
    // char buffer[6];
    paths = get_paths(envp);
    correct_path = get_correct_path(paths, "cat");
    printf("CORRECT=%s\n", correct_path);
    free(correct_path);
    // execve(paths[j], options, envp);
    // if (pipe(pipefd) ==  -1)
    //     return (1);

    // printf("Before fork\n");
    // pid = fork();
    // if (pid == -1)
    //     return (1);
    // if (pid == 0)
    // {
    //     // La valeur de retour de fork est 0, ce qui veut dire qu'on est dans le processus fils
    //     close(pipefd[0]);
    //     write(pipefd[1], "Romeo", 5);
    //     close(pipefd[1]);

    //     printf("---------child fork---------\n");
    //     printf("pid = %d\n", pid);
    //     printf("Fils : Je suis le fils, mon pid interne est %d.\n", pid);
    // }
    // else if (pid > 0)
    // {
    //     // La valeur de retour de fork est différente de 0, ce qui veut dire qu'on est dans le processus père
    //     wait(&status);
    //     printf("pid %d terminated\n", status);
    //     printf("---------parent fork---------\n");
    //     close(pipefd[1]);
    //     read(pipefd[0], buffer, 5);
    //     printf("Le secret est %s\n", buffer);
    //     close(pipefd[0]);
    //     printf("pid = %d\n", pid);
    //     printf("Pere : Je suis le pere, le pid de mon fils est %d.\n", pid);
    // }
 
    return (0);
}