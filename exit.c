/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 06:40:46 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/01 17:05:36 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	ft_exit(char **res, t_command *cmd)
{
	int i;

	i = 0;
	if (res[1] && !res[2])
	{
		while (res[1][i] && ft_isdigit(res[1][i]))
			i++;
		if (i == ft_strlen(res[1]))
		{
			if (g_sig.sig == 0)
				cmd->cmd_rv = ft_atoi(res[1]);
			else
			{
				if (g_sig.sig == 1)
					cmd->cmd_rv = 130;
				else
					cmd->cmd_rv = 131;
			}
			exit(cmd->cmd_rv);
		}
		else
		{
			write(1, "exit: ", 6);
			write(1, res[1], ft_strlen(res[1]));
			write(1, ": numeric argument required\n", 28);
			cmd->cmd_rv = 2;
			exit(2);
		}
	}
	else if (res[1] && res[2] && g_sig.sig == 0)
	{
		write(1, "bash: exit: too many arguments\n", 30);
		cmd->cmd_rv = 1;
		exit(1);
	}
	else
	{
		cmd->cmd_rv = 0;
		exit(0);
	}
}