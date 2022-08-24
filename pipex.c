#include <unistd.h>

void pipex()
{

}

int main(int argc, char **argv, char **envp)
{
    char *options[3] = {"cat", "file2", NULL};

    (void)argc;
    (void)argv;
    execve("/usr/bin/cat", options, envp);
    return (0);
}