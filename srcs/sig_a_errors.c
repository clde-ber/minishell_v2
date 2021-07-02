/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_a_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:56:27 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	errors(t_command *cmd)
{
	cmd->cmd_rv = 1;
}

void	handle_signal(int code)
{
	if (code == 2)
	{
		g_sig.sig = 1;
		if (g_sig.boolean == 1 || g_sig.boolean > 1)
		{
			if (g_sig.boolean > 1)
				g_sig.boolean = -1;
			ft_putstr_fd("\n", 1);
		}
		else
			ft_putstr_fd("^C\n***minishell*** > ", 1);
	}
	else if (code == 3)
	{
		if (g_sig.boolean == 1)
		{
			g_sig.sig = 2;
			ft_putstr_fd("Quit (core dumped)\n", 1);
		}
		else if (g_sig.boolean > 1)
			g_sig.boolean = -1;
	}
	g_sig.stop = 1;
}
