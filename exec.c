#include "minishell.h"

/*
** Functions that are similar to launch_exe ones, using execve to execute any command. Here, functions are supposed to handle not only the "./"
** one but any shell commands. Variable $PATH environment value is splited with ':' character to help testing different locations for our 
** command binaries - for example /bin/. Execve is called with first command line argument until it returns correctly, that is until it finds where
** the command binaries are stored. Then it executes the command or prints an error.
*/

char **arguments(char **res, int j, char **args, char *path)
{
    char **argv;
    char **p_bin;
    char *str;
    int i;
    int k;

    i = 1;
    k = 0;
    p_bin = parse_path(path, ':');
    while (p_bin[k])
        k++;
    str = ft_strjoin(p_bin[0], "/");
    argv = NULL;
    if (!(argv = malloc(sizeof(char *) * (j + 2))))
        return (0);
    argv[0] = ft_strjoin(str, res[0]);
    while (i < j)
    {
        argv[i] = ft_strdup(args[i - 1]);
        i++;
    }
    argv[i] = NULL;
    free(str);
    ft_free(p_bin, k + 1);
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

int exit_status(int status)
{
    return (status % 255);
}

int exec_command(char **args, char **res, char *path, int j)
{
    pid_t pid;
    int ret;
    int status;
    int i;
    int k;
    char **tabl;
    int count;
    char *str;
    char **p_bin;
    char **env;

    pid = 0;
    ret = 0;
    errno = 0;
    status = 0;
    tabl = arguments(res, j, args, path);
    i = 0;
    count = 0;
    str = NULL;
    p_bin = NULL;
    env = NULL;
    k = 0;
    while (tabl[k])
        k++;
// readdir must be called to print correct error.
// Fork duplicates the process so the parent process doesn't return when the child process does.
    if ((pid = fork()) == 0)
    {
        i = 0;
        k = 0;
        p_bin = parse_path(path, ':');
        env = environment(path);
        while(env[k])
            k++;
        while (p_bin[i])
		{
            free(tabl[0]);
            str = ft_strjoin(p_bin[i], "/");
            tabl[0] = ft_strjoin(str, res[0]);
            // int x = 0;
            // while (tabl[x])
            // {
            //     ft_putstr_nbr(x, 1);
            //     ft_putstr_fd(" ", 1);
            //     ft_putstr_fd(tabl[x], 1);
            //     ft_putstr_fd("\n", 1);
            //     x++;
            // }
            if ((ret = execve(tabl[0], tabl, env)) == -1)
                count++;
            i++;
            free(str);
        }
        if (i == count)
        {
            free(tabl[0]);
            ft_free(env, k + 1);
            ft_free(p_bin, i + 1);
            printf("%s : Command not found\n", res[0]);
            exit(33151);
        }
        free(tabl[0]);
        ft_free(env, k + 1);
        ft_free(p_bin, i + 1);
        exit(status);
    }
//    if (ret == -1)
//        return (-1);
    ft_free(tabl, k + 1);
    waitpid(ret, &status, 0);
    return (exit_status(status));
// waitpid waits for the program to be finished. 
}

//res[0] needs to be trimed so strings with simple or double quotes are managed.

int set_args(char **res, char *path, t_command *cmd)
{
    int i;
    int index;
    char **args;
    int ret;
    char **clc;
    int k;

    i = 0;
    index = 0;
    ret = 0;
    clc = NULL;
    k = 0;
    // char **text = check_redir_exec(res);
    // while (text[i])
    //     i++;
    // if (i > 1)
    // {
    //     if (!(args = malloc(sizeof(char *) * i)))
    //         return (0);
    //     while (index + 1 < i)
    //     {
    //         args[index] = ft_strdup(text[index + 1]);
    //         index++;
    //     }
    //     args[index] = NULL;
    //     ret = exec_command(args, text, path, i);
    //     cmd->cmd_rv = ret;
    //     ft_free(args, index + 1);
    // }
    // else
    // {
    //     ret = exec_command((clc = ft_calloc(2, sizeof(char *))), text, path, 1);
    //     cmd->cmd_rv = ret;
    //     while (clc[k])
    //         k++;
    //     ft_free(clc, k + 1);
    // }
    // return (0);
    while (res[i])
        i++;
    if (i > 1)
    {
        if (!(args = malloc(sizeof(char *) * i)))
            return (0);
        while (index + 1 < i)
        {
            args[index] = ft_strdup(res[index + 1]);
            index++;
        }
        args[index] = NULL;
        ret = exec_command(args, res, path, i);
        cmd->cmd_rv = ret;
        ft_free(args, index + 1);
    }
    else
    {
        ret = exec_command((clc = ft_calloc(2, sizeof(char *))), res, path, 1);
        cmd->cmd_rv = ret;
        while (clc[k])
            k++;
        ft_free(clc, k + 1);
    }
    return (0);
}