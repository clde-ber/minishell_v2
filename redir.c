#include "minishell.h"

/*
**All functions for redirections (> >> <) shall go there. A work in progress.
*/

void    redir_file(char **res, char *output, int c)
{
    int fd;
    int i;

    i = 0;
    if (c == 0)
        fd = open(res[2], O_CREAT | O_RDWR | O_TRUNC, 0777);
    else 
        fd = open(res[2], O_APPEND | O_RDWR, 0777);
    while (output[i])
        write(fd, &output[i++], 1);
    close(fd);
    return ;
}

int    check_redir(char **res, int i, char *output)
{
    if (!res[i])
        return (0);
    if (ft_strcmp(res[i], ">") == 0)
        redir_file(res, output, 0);
    else if (ft_strcmp(res[i], ">>") == 0)
        redir_file(res, output, 1);
    // else if (ft_strcmp(res[i], "<") == 0)
    //     redir_ext(command, output);
    else
        return (0);
    return (1);
}