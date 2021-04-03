#include "minishell.h"

/*
** Functions that are similar to launch_exe ones, using execve to execute any command. Here, functions are supposed to handle not only the "./"
** one but any shell commands. Variable $PATH environment value is splited with ':' character to help testing different locations for our 
** command binaries - for example /bin/. Execve is called with first command line argument until it returns correctly, that is until it finds where
** the command binaries are stored. Then it executes the command or prints an error.
*/

int read_dir(char *path, char *command)
{
    DIR *dir;
    struct dirent *s_dir;
    if (!(dir = opendir(path)))
	{
	    printf("%s\n", strerror(errno));
		return (0);
	}
    return (1);
}

char **arguments(char **res, int j, char **args, char *path)
{
    char **argv;
    int i;

    i = 1;
    argv = NULL;
    if (!(argv = malloc(sizeof(char *) * (j + 2))))
        return (0);
    argv[0] = ft_strjoin(ft_strjoin(parse_path(path, ':')[0], "/"), res[0]);
    while (i < j)
    {
        argv[i] = ft_strdup(args[i - 1]);
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

char **environment(char *path)
{
    char **envp;

    envp = NULL;
    if (!(envp = malloc(sizeof(char *) * 2)))
        return (0);
    envp[0] = ft_strjoin("PATH=", path);
    envp[1] = NULL;
    return (envp);
}

int exit_status(int status, int errno)
{
    if (WIFEXITED(status))
        return (0);
    else
	{
        printf("%s\n", strerror(errno));
		exit(0);
	}
}

int exec_command(char **args, char **res, char *path, int j)
{
    pid_t pid;
    int ret;
    int status;
    int i;
    char **tab;

    pid = 0;
    ret = 0;
    errno = 0;
    status = 0;
    tab = arguments(res, j, args, path);
    i = 0;
// readdir must be called to print correct error.
// Fork duplicates the process so the parent process doesn't return when the child process does.
    if ((pid = fork()) == 0)
    {
        while (parse_path(path, ':')[i])
		{
            free(tab[0]);
            tab[0] = ft_strjoin(ft_strjoin(parse_path(path, ':')[i], "/"), res[0]);
            ret = execve(tab[0], tab, environment(path));
        	i++;
        }
    }
    waitpid(ret, &status, 0);
    return (exit_status(status, errno));
// waitpid waits for the program to be finished. 
}

//res[0] needs to be trimed so strings with simple or double quotes are managed.

int set_args(char **res, char **env, char *path)
{
    int i;
    int index;
    char **args;

    i = 0;
    index = 0;
    while (res[i])
        i++;
    if (i > 1)
    {
        if (!(args = malloc(sizeof(char *) * i)))
            return (0);
        while (index + 1 < i)
        {
            args[index] = res[index + 1];
            index++;
        }
        args[index] = NULL;
        exec_command(args, res, path, i);
    }
    else
        exec_command(ft_calloc(2, sizeof(char *)), res, path, 1);
    return (0);
}