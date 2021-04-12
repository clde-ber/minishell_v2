#include "minishell.h"

char **destroy_res(char **res)
{
    char **tab;
    int i;
    int m;
    int j;

    i = 0;
    j = 0;
    m = count_tabs(res);
    if (!(tab = malloc(sizeof(char *) * (m - 1))))
        return (NULL);
    while (res[i])
    {
        ft_putstr_fd(res[i], 1);
        if (ft_strcmp(res[i], ">") != 0 && ft_strcmp(res[i], ">>") != 0 && ft_strcmp(res[i], "<"))
        {
            tab[j] = ft_strdup(res[i]);
            j++;
            i++;
        }
        else
            i += 2;
    }
    tab[j] = NULL;
    return (tab);
}

int     open_fds_out(char **res, int i, int m)
{
    int fd;

    i++;
    close(1);
    if (m == 0)
        fd = open(res[i], O_CREAT | O_RDWR | O_TRUNC, 0777);
    else 
        fd = open(res[i], O_APPEND | O_RDWR, 0777);
    return (fd);
}

int     open_fds_in(char **res, int i)
{
    int fd;

    i++;
    close(0);
    fd = open(res[i], O_RDONLY, 0777);
    return (fd);
}

int     handle_pipe(char **res, int i)
{
    int fds[2];

    close(0);
    close(1);
    if (pipe(fds) == -1)
        return (-1);
    return (127);
}

int    handle_fds(char **res)
{
    int i;

    i = 0;
    while(res[i])
    {
        if (ft_strcmp(res[i], ">") == 0)
            return(open_fds_out(res, i, 0));
        else if (ft_strcmp(res[i], ">>") == 0)
            return(open_fds_out(res, i, 1));
        else if (ft_strcmp(res[i], "<") == 0)
            return(open_fds_in(res, i));
        else if (ft_strcmp(res[i], "|") == 0)
            return (handle_pipe(res, i));
        i++;
    }
    return (-127);
}

int count_before_pipe(char **res)
{
    int i;

    i = 0;
    while(res[i])
    {
        if (ft_strcmp(res[i], "|") == 0)
            return (i);
        i++;
    }
    return (0);
}

void    line_after_pipe(char **res, int i, t_fd *f)
{
    int j;
    int m;

    j = 0;
    i++;
    m = i;
    while (res[i])
        i++;
    if (f->save_pipe[0] != NULL)
        free_tabtab(f->save_pipe);
    if (!(f->save_pipe = malloc(sizeof(char *) * ((i - m) + 1))))
        return (NULL);
    i = m;
    while (res[i])
    {
        f->save_pipe[j] = ft_strdup(res[i]);
        j++;
        i++;
    }
    f->save_pipe[j] = NULL;
}

char    **save_after_pipe(char **res, t_fd *f)
{
    int i;
    int j;
    char **tab;

    j = count_before_pipe(res);
    if(!(tab = malloc(sizeof(char *) * (j + 1))))
        return (NULL);
    while (i < j)
    {
        tab[j] = ft_strdup(res[i]);
        j++;
        i++;
    }
    tab[j] = NULL;
    line_after_pipe(res, i, f);
}

char **check_redir(char **res, t_fd *f)
{
    int fd;
    char **tab;

    fd = handle_fds(res);
    if (fd == -127)
        return (res);
    if (fd = 127)
        return (save_after_pipe(res, f));
    if (fd == -1)
    {
        restore_fds(f);
        return (NULL);
    }
    tab = destroy_res(res);
    return (tab);
}