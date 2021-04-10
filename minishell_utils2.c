# include "minishell.h"

void init_structs(t_command *cmd)
{
    cmd->path = NULL;
    cmd->index = 0;
    cmd->cmd_rv = 0;
}