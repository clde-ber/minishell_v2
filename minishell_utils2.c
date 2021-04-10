#include "minishell.h"

char    *cut_after_punct(char *dest, char *line)
{
    int i;
    char *buf;

    i = ft_strchr_bis(line, ';');
    if (i == -1)
    {
        dest = NULL;
        return (dest);
    }
    dest = ft_substr(line, i + 1, ft_strlen(line) - i);
    return (dest);
}

int     count_tabs(char **res)
{
    int j;

    j = 0;
    if (!res[j])
        return (j);
    while (res[j] != NULL)
        j++;
    return (j);
}

void    free_tabtab(char **res)
{
    int i;

    i = 0;
    while (res[i] != NULL)
        free(res[i++]);
    free(res);
}