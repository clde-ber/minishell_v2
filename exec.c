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
    int y;
    char *to_free;
    char *to_free2;

    i = 1;
    pid = 0;
    ret = 0;
    errno = 0;
    status = 0;
    x = 0;
    y = 0;
    if (!(argv = malloc(sizeof(char *) * (j + 2))))
        return (0);
    tab = parse_path(path, ':');
    while (tab[y])
        y++;
    to_free2 = ft_strjoin(tab[0], "/");
    argv[0] = ft_strjoin(to_free2, res[0]);
    free(to_free2);
    while (i < j)
    {
        argv[i] = ft_strdup(args[i - 1]);
        i++;
    }
    argv[i] = NULL;
    char *envp[]={(to_free = ft_strjoin("PATH=", path)), NULL};
    if ((pid = fork()) == 0)
    {
        while (tab[x])
		{
            free(argv[0]);
            to_free2 = ft_strjoin(tab[x], "/");
            argv[0] = ft_strjoin(to_free2, res[0]);
            if ((ret = execve(argv[0], argv, envp)) == -1)
            free(to_free2);
        	x++;
        }
    }
    waitpid(ret, &status, 0);
    ft_free(tab, y + 1);
    ft_free(argv, j + 1);
    free(to_free);
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
    char **to_free;

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
    //    ft_free(args, index + 1);
    }
    else
    {
        exec_command((to_free = ft_calloc(2, sizeof(char *))), res, path, 1);
    //    ft_free(to_free, 2);
    }
    return (0);
}