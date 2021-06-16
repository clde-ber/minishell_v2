/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_a_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:56:27 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/09 17:04:12 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	errors(t_command *cmd)
{
	cmd->cmd_rv = 1;
}

void	handle_signal(int code)
{
	if (code == 2)
	{
		g_sig.sig = 1;
		if (g_sig.boolean == 1)
			write(1, "\n", 1);
		else
			write(1, "\n***minishell*** > ", 19);
	}
	else if (code == 3)
	{
		if (g_sig.boolean == 1)
		{
			g_sig.sig = 2;
			write(1, "Quit (core dumped)\n", 19);
		}
	}
}
