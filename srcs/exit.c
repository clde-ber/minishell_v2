/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 06:40:46 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/08 16:34:32 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

void	exit_error_no_nb(char **res, t_command *cmd)
{
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(res[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	cmd->cmd_rv = 2;
}

void	exit_too_many_args(t_command *cmd)
{
	ft_putstr_fd("bash: exit: too many arguments\n", 2);
	cmd->cmd_rv = 1;
}

void	exit_code(char **res, t_command *cmd)
{
	if (g_sig.sig == 0)
	{
		cmd->cmd_rv = ft_atoi(res[1]);
		if (cmd->cmd_rv < 0)
			cmd->cmd_rv = 256 + cmd->cmd_rv;
	}
	else
	{
		if (g_sig.sig == 1)
			cmd->cmd_rv = 130;
		else
			cmd->cmd_rv = 131;
	}
}

void	ft_exit(int i, char **res, t_command *cmd)
{
	int	boolean;

	boolean = 0;
	if (g_sig.boolean >= 2 || g_sig.sig == -1)
		return ;
	if (res[1] && !res[2])
	{
		while ((res[1][i] && ft_isdigit(res[1][i])) || \
		(i == 0 && (res[1][i] == '+' || res[1][i] == '-')))
			i++;
		if (i == (int)ft_strlen(res[1]))
			exit_code(res, cmd);
		else
			exit_error_no_nb(res, cmd);
	}
	else if (res[1] && res[2] && g_sig.sig == 0)
	{
		exit_too_many_args(cmd);
		boolean = 1;
	}
	if (boolean != 1)
		exit(cmd->cmd_rv);
}
