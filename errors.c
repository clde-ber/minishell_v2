#include "minishell.h"

int errors(char **res, t_command *cmd)
{
    write (1, "Not a valid identifier\n", 23);
    cmd->cmd_rv = 1;
}