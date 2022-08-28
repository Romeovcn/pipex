# include "pipex.h"

void first_child(t_data data, char **argv, char **envp)
{
	char **options;
	char *correct_path;

	options = ft_split(argv[2], ' ');
   	correct_path = get_correct_path(data.paths, options[0]);
	dup2(data.pipe_fd[1], 1);
	dup2(data.infile_fd, 0);
    close(data.pipe_fd[0]);
    close(data.pipe_fd[1]);
    execve(correct_path, options, envp);
	//write(2, strerror(errno), ft_strlen(strerror(errno)));
    //write(2, "\n", 1);
	exit(1);
}

void second_child(t_data data, char **argv, char **envp)
{
	char **options;
	char *correct_path;

	options = ft_split(argv[3], ' ');
	correct_path = get_correct_path(data.paths, options[0]);
	dup2(data.pipe_fd[0], 0);
	//dup2(outfile_fd, 1);
	close(data.pipe_fd[0]);
  	close(data.pipe_fd[1]);
    execve(correct_path, options, envp);
	exit(1);
}

void get_fds(t_data *data, char **argv)
{
	(*data).infile_fd = open(argv[1], O_RDONLY);
	if ((*data).infile_fd == -1)
	{
		// free paths
		write(2, strerror(errno), ft_strlen(strerror(errno)));
        write(2, "\n", 1);
		exit(1);
	}
	(*data).outfile_fd = open(argv[4], O_WRONLY);
	if ((*data).outfile_fd == -1)
	{
		// free paths
		close((*data).infile_fd);
		write(2, strerror(errno), ft_strlen(strerror(errno)));
        write(2, "\n", 1);
		exit(1);
	}
    if (pipe((*data).pipe_fd) ==  -1)
	{
		ft_printf("Couldn't open pipe.\n");
        exit(1);
	}
}

void close_fds(t_data data)
{
	close(data.pipe_fd[0]);
    close(data.pipe_fd[1]);
	close(data.infile_fd);
	close(data.outfile_fd);
}

int main(int argc, char **argv, char **envp)
{
	t_data data;
	char buffer[6];
	pid_t respid;
	int status;

	if (argc != 5)
	{
		ft_printf("Argument(s) missing or too much arguments\n");
		exit(1);
	}
    data.paths = get_paths(envp);
	get_fds(&data, argv);
	data.pid_1 = fork();
	if (data.pid_1 == -1)
		return (1);
	if (data.pid_1 == 0)
		first_child(data, argv, envp);
	data.pid_2 = fork();
	if (data.pid_2 == -1)
		return (1);
	if (data.pid_2 == 0)
		second_child(data, argv, envp);
	close_fds(data);
	waitpid(data.pid_1, &status, 0);
    //if (WEXITSTATUS(status) == 0)
    //    printf("Parent : It exited successfully, exit code %d %d\n", WEXITSTATUS(status), WIFEXITED(status));
    //else
	//{
    //    printf("Parent : It was interrupted...\n");
	//	exit(1);
	//}
	waitpid(data.pid_2, NULL, 0);
	ft_printf("Im the parent my PID is %d\n", getpid());
}