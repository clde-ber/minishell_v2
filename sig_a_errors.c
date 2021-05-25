/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_a_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:56:27 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/25 14:03:16 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors(t_command *cmd)
{
//    write (1, "Not a valid identifier\n", 23);
	cmd->cmd_rv = 1;
}

// ctrl-c -> ^C -> prompt -> 130 : Command not found
// ctrl-\ -> Quit (core dumped) ->prompt -> 131 : Comand not found
// ctrl-d -> prompt -> 0 : Command not found

void	handle_signal(int code)
{
	if (code == 2)
	//ctrl-c
	{
		g_sig = 1;
		write(1, "\n", 1);
	}
	else if (code == 3)
	//ctrl-antislash
	{
		g_sig = 2;
		write(1, "Quit (core dumped)\n", 19);
	}
}
