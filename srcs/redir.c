/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:06:50 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/11 10:55:01 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	go_e(char **tabl, t_list *var_env, t_command *cmd, int j)
{
	if (ft_strcmp(tabl[0], "echo") == 0 || ft_strcmp(tabl[0], "export") == 0 \
	|| ft_strcmp(tabl[0], "env") == 0 || ft_strcmp(tabl[0], "exit") == 0)
	{
		if (ft_strcmp(tabl[0], "echo") == 0)
			ft_echo(tabl, cmd);
		if (ft_strcmp(tabl[0], "export") == 0 && ((tabl[1] && cmd->res[1]) \
		|| (!tabl[1] && cmd->res[1] && ft_strchr(cmd->res[1], '='))))
		{
			check_doublons_cl(tabl, NULL, NULL, 0);
			set_env(tabl, var_env, cmd, j);
			reset_cmd_path(var_env, cmd);
		}
		else if (ft_strcmp(tabl[0], "export") == 0)
			print_sorted_env(var_env, cmd);
		if (ft_strcmp(tabl[0], "env") == 0)
			print_env(var_env, cmd);
		if (ft_strcmp(tabl[0], "exit") == 0 && g_sig.stop != 1)
		{
			cmd->cmd_rv = 0;
			ft_exit(0, tabl, cmd);
		}
	}
	else
		set_args(tabl, cmd);
	return (0);
}

int	tabl_is_null(int *j, char **tabl, t_command *cmd)
{
	*j = 0;
	if (tabl[0] == NULL)
	{
		cmd->cmd_rv = 0;
		free(tabl);
		tabl = NULL;
		return (1);
	}
	while (tabl[*j])
		(*j)++;
	return (0);
}

void	handle_cmd_rv(char **tabl, t_command *cmd)
{
	if (g_sig.sig == 1)
		cmd->cmd_rv = 130;
	if (g_sig.sig == 2)
		cmd->cmd_rv = 131;
	if (ft_strcmp(tabl[0], "$?") == 0)
	{
		ft_putstr_fd("$?", 2);
		ft_putstr_fd(" : Command not found\n", 2);
		cmd->cmd_rv = 127;
	}
	if (g_sig.sig == 1 || g_sig.sig == 2)
		g_sig.sig = 0;
	free_tabtab(tabl);
}

int	go_instruction(char **tabl, t_list *var_env, t_command *cmd, char **env)
{
	int	j;

	if (tabl_is_null(&j, tabl, cmd))
		return (0);
	if (tabl[0][0] == 'e' && ft_strcmp(tabl[0], "$?"))
		go_e(tabl, var_env, cmd, j);
	else if (ft_strcmp(tabl[0], "pwd") == 0 && ft_strcmp(tabl[0], "$?"))
		ft_pwd(cmd, var_env);
	else if (ft_strcmp(tabl[0], "cd") == 0 && tabl[1] && ft_strcmp(tabl[1], "") \
	&& ft_strcmp(tabl[0], "$?"))
		ft_cd(tabl, var_env, cmd);
	else if (ft_strcmp(tabl[0], "cd") == 0 && (!tabl[1] || \
	ft_strcmp(tabl[1], "") == 0) && ft_strcmp(tabl[0], "$?"))
		cd_no_arg(var_env, cmd);
	else if (tabl[0][0] == '.' && tabl[0][1] == '/' && ft_strcmp(tabl[0], "$?"))
		find_exe(tabl[0], env, cmd);
	else if (ft_strcmp(tabl[0], "unset") == 0 && tabl[1] && ft_strcmp(tabl[0], \
	"$?"))
		unset(var_env, tabl, cmd, j);
	else if (ft_strcmp(tabl[0], "unset") == 0 && ft_strcmp(tabl[0], "$?"))
		errors(cmd);
	else if (ft_strcmp(tabl[0], "$?"))
		set_args(tabl, cmd);
	handle_cmd_rv(tabl, cmd);
	return (0);
}

int	redir_and_send(t_fd *f, t_list *var_env, t_command *cmd, char **env)
{
	if (cmd->env)
		free_tabtab(cmd->env);
	cmd->env = put_list_in_tab(var_env);
	if ((chrtabtab(f->res, "|") == -1 || chrtabtab(f->first_res, "\\|") != -1) \
	&& (chrtabtab(f->res, ">") == -1 || chrtabtab(f->first_res, "\\>") != -1) \
	&& (chrtabtab(f->res, "<") == -1 || chrtabtab(f->first_res, "\\<") != -1) \
	&& (chrtabtab(f->res, ">>") == -1 || chrtabtab(f->first_res, "\\>>") != -1))
		return (go_instruction(copy_tabtab(f->res), var_env, cmd, env));
	else if (check_valid_res(f->res))
		return (faulty_redir(cmd));
	else if (chrtabtab(f->res, "|") == -1 || chrtabtab(f->first_res, "\\|") \
	!= -1)
		return (go_instruction(end_redir(f->res, f), var_env, cmd, env));
	else
	{
		if (count_pipes(f->res) == 1)
			return (go_pipe(f, var_env, cmd, env));
		else
			return (handle_multipipes(f, var_env, cmd, env));
	}
	free_tabtab(f->res);
	return (2);
}
