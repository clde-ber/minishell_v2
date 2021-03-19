/*
**All functions pertaining the echo implementation. WIP: echo doc disappears to be attributed to redirection functions.
** echo stdin goes into echo main and creates char *output to be passed if redirection exists or to be printed.
*/

/*
**All functions for redirections (> >> <) shall go there. A work in progress.
*/

#include "minishell.h"

void    redir_file(char *str, char *output)
{

}

void    check_redir(char *command, char *output)
{
/*    char *ret;
    if ((ret = strchr(str, '<')) != NULL)
        redir_ext(command, output);
    else if ((ret = strchr(str, '>')) != NULL)
    {
        if (ret++ == '>')
            redir_EOF(command, output);
        redir_file(command, output);
    }*/
}