#include "minishell.h"

/*
**All functions for redirections (> >> <) shall go there. A work in progress.
*/

void    redir_file(char **res, int i, char *output, int c)
{
    int fd;

    i++;
    if (c == 0)
        fd = open(res[i], O_CREAT | O_RDWR | O_TRUNC, 0777);
    else 
        fd = open(res[i], O_APPEND | O_RDWR, 0777);
    ft_putstr_fd(output, fd);
    close(fd);
    return ;
}

char    *get_content_file(int fd)
{
    char *line;
    char *end;
    char *buf;
    char *buf2;

    end = NULL;
    line = NULL;
    while (get_next_line(fd, &line) == 1)
    {
        buf = ft_strjoin(line, "\n");
        if (end == NULL)
            end = ft_strdup(buf);
        else
        {
            buf2 = ft_strjoin(end, buf);
            free(end);
            end = ft_strdup(buf2);
            free(buf2);
        }
        free(buf);
        free(line);
    }
    // ft_putstr_fd(end, 1);
    return (end);
}

char   **get_after_redir(char **res, int i, char *content)
{
    char **tab;
    int j;
    int m;

    j = 0;
    m = count_tabs(res);
    // m--;
    if(!(tab = malloc(sizeof(char *) * m)))
        return (NULL);
    while (j < i)
    {
        tab[j] = ft_strdup(res[j]);
        // ft_putstr_fd(tab[j], 1);
        j++;
    }
    tab[j] = ft_strdup(content);
    // ft_putstr_fd(tab[j], 1);
    j++;
    i += 2;
    while (res[i])
    {
        tab[j] = ft_strdup(res[i]);
        // ft_putstr_fd(tab[j], 1);
        j++;
        i++;
    }
    tab[j] = NULL;
    free_tabtab(res);
    return (tab);
}

char **redir_ext(char **res, int i)
{
    int fd;
    char *content;
    char **tab;
    
    i++;
    fd = open(res[i], O_RDONLY, 0555);
    content = get_content_file(fd);
    i--;
    tab = get_after_redir(res, i, content);
    return (tab);
}

char    **redir_ext_check(char **res)
{
    int i;
    char **tab;

    i = 0;
    while (res[i])
    {
        if (ft_strcmp(res[i], "<") == 0)
        {
            // free(res);
            tab = redir_ext(res, i);
        }
        i++;
    }
    return (tab);
}

int    check_redir(char **res, int i, char *output)
{
    if (!res[i])
        return (0);
    if (ft_strcmp(res[i], ">") == 0)
        redir_file(res, i, output, 0);
    else if (ft_strcmp(res[i], ">>") == 0)
        redir_file(res, i, output, 1);
    // else if (ft_strcmp(res[i], "<") == 0)
    //     redir_ext(res, i, output);
    else
        return (0);
    return (1);
}