#include "minishell.h"

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

int exec_command(char **args, char **res, char *path, int j)
{
    pid_t pid;
    int ret;
    int status;
    int i;
    char **argv;
    char **tab;
    int x;

    i = 1;
    pid = 0;
    ret = 0;
    errno = 0;
    status = 0;
    x = 0;
    if (!(argv = malloc(sizeof(char *) * (j + 2))))
        return (0);
    tab = parse_path(path, ':');
    argv[0] = ft_strjoin(ft_strjoin(tab[0], "/"), res[0]);
    while (i < j)
    {
        argv[i] = ft_strdup(args[i - 1]);
        i++;
    }
    argv[i] = NULL;
    char *envp[]={ft_strjoin("PATH=", path), NULL};
    if ((pid = fork()) == 0)
    {
        while (tab[x])
		{
            argv[0] = ft_strjoin(ft_strjoin(tab[x], "/"), res[0]);
            if (ret = execve(argv[0], argv, envp) == -1)
        	x++;
        }
    }
    waitpid(ret, &status, 0);
	if (WIFEXITED(status))
        return (0);
    else
	{
        printf("%s\n", strerror(errno));
		exit(0);
	}
    return (0);
// waitpid attd que le programme se termine 
}

int set_args(char **res, char **env, char *path)
{
    int i;
    int index;
    char **args;

    i = 0;
    index = 0;
    while (res[i])
        i++;
    if (!(args = malloc(sizeof(char *) * i)))
        return (0);
    while (index + 1 < i)
    {
        args[index] = ft_strdup(res[index + 1]);
        index++;
    }
    args[index] = NULL;
    if (i > 1)
        exec_command(args, res, ft_strdup(path), i);
    else
        exec_command(ft_calloc(2, sizeof(char *)), res, ft_strdup(path), 1);
    return (0);
}