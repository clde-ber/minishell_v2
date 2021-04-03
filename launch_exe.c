#include "minishell.h"

/*
** Functions that search and launch an executable when first command line agurment begins with "./". The program reads directories and compares
** their names to the ones in path. At the end, it checks whether the filename is correct or exists. If the last directory can't be opened, it returns
** an error. If execve - that executes the command - returns an error, it prints error accordingly. If command is interrupted by a signal, it prints an error.
*/

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