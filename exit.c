/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 06:40:46 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/08 14:42:09 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	exit_error_no_nb(char **res, t_command *cmd)
{
	write(1, "exit: ", 6);
	write(1, res[1], ft_strlen(res[1]));
	write(1, ": numeric argument required\n", 28);
	cmd->cmd_rv = 2;
}

void	exit_too_many_args(t_command *cmd)
{
	write(1, "bash: exit: too many arguments\n", 30);
	cmd->cmd_rv = 1;
}

void	exit_no_code(char **res, int i, t_command *cmd)
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
			exit_no_code(res, i, cmd);
			exit(cmd->cmd_rv);
		}
		else
		{
			exit_error_no_nb(res, cmd);
			exit(2);
		}
	}
	else if (res[1] && res[2] && g_sig.sig == 0)
	{
		exit_too_many_args(cmd);
		exit(1);
	}
	cmd->cmd_rv = 0;
	exit(0);
}