#include "minishell.h"

void errors(t_command *cmd)
{
    write (1, "Not a valid identifier\n", 23);
    cmd->cmd_rv = 1;
}

// ctrl-c -> ^C -> prompt -> 130 : Command not found
// ctrl-\ -> Quit (core dumped) ->prompt -> 131 : Comand not found
// ctrl-d -> prompt -> 0 : Command not found

void handle_signal(int code)
{
    if (code == 2) //ctrl-c
    {
        sig = 1;
        write(1, "\n", 1);
    }
    else if (code == 3) //ctrl-antislash
    {
        sig = 2;
        write(1, "Quit (core dumped)\n***minishell*** > ", 37);
    }
}