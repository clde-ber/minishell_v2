#include "minishell.h"

int errors(char **res)
{
    if (ft_strcmp("export", res[0]) == 0)
        write (1, "Not a valid identifier\n", 23);
    exit(0);
}