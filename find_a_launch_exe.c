#include "minishell.h"

char	*ft_get_filename(const char *s, int c)
{
	char	*str;
    int i;

	str = (char *)s;
    i = ft_strlen(str);
    while (i)
    {
        if (str[i] == c)
            return (ft_strdup((const char *)&str[i + 1]));
        i--;
    }
    return (NULL);
}

char *get_path(char *path, char c)
{
    char	*str;
    int i;
    int j;

    j = 1;
	str = (char *)path;
    i = ft_strlen(str);
    while (i)
    {
        if (str[i] == c)
        {
            while (str[i + j])
            {
                str[i + j] = '\0';
                j++;
            }
            return (str);
        }
        i--;
    }
    return (NULL);
}

static char **arg_tab(char *exe, char *path, char **env)
{
    char **ret;

    if (!(ret = malloc(sizeof(char *) * 3)))
        return (0);
    ret[0] = ft_strjoin(path, exe);
    ret[1] = (char *)env;
    ret[2] = NULL;
    return (ret);
}

static char **env_tab(char *path)
{
    char **ret;

    if (!(ret = malloc(sizeof(char *) * 3)))
        return (0);
    ret[0] = ft_strjoin("HOME=", ".");
    ret[1] = ft_strjoin("PATH=", path);
    ret[2] = NULL;
    return (ret);
}

int launch_exe(char *exe, char *path, char **env)
{
    pid_t pid;
    int ret;
    int status;
    char **argv;
    char **envp;

    pid = 0;
    ret = 0;
    errno = 0;
    status = 0;
    argv = arg_tab(exe, path, env);
    envp = env_tab(path);
    if ((pid = fork()) == 0)
    {
        if ((ret = execve(argv[0], argv, envp)) == -1)
		{
		    printf("%s\n", strerror(errno));
			exit(0);
		}
    }
    waitpid(ret, &status, 0);
	return (exit_status(status, errno));
// waitpid attd que le programme se termine 
}

void find_exe(int index, char *path, char **env)
{
    DIR *dir;
    int i;
    char *str;
    struct dirent *st_dir;

    i = 0;
    st_dir = NULL;
    str = ft_get_filename(path, '/');
    errno = 0;
    if (!(dir = opendir(get_path(path, '/'))))
	{
	    printf("%s\n", strerror(errno));
		return ;
	}
    while ((st_dir = readdir(dir)))
        if (ft_strcmp(st_dir->d_name, str) == 0)
        {
            launch_exe(st_dir->d_name, path, env);
            closedir(dir);
            return ;
        }
    if (errno)
        printf("%s\n", strerror(errno));
    else
        launch_exe(str, path, env);
}