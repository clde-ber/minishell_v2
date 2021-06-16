/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:06:50 by budal-bi          #+#    #+#             */
/*   Updated: 2021/06/16 15:45:05 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**divide_pipe(t_fd *f)
{
	int		m;
	int		i;
	char	**tabl;

	i = 0;
	m = count_tabs(f->res) - chrtabtab(f->res, "|");
	f->save_pipe = malloc(sizeof(char *) * (m + 2));
	tabl = malloc(sizeof(char *) * (chrtabtab(f->res, "|") + 2));
	if (!(tabl) || !(f->save_pipe))
		return (NULL);
	while (i < chrtabtab(f->res, "|"))
	{
		tabl[i] = ft_strdup(f->res[i]);
		i++;
	}
	tabl[i] = NULL;
	i = 0;
	while (f->res[chrtabtab(f->res, "|") + i + 1])
	{
		f->save_pipe[i] = ft_strdup(f->res[chrtabtab(f->res, "|") + i + 1]);
		i++;
	}
	f->save_pipe[i] = NULL;
	return (tabl);
}

int	go_e(char **tabl, t_list *var_env, t_command *cmd, int j)
{
	if (ft_strcmp(tabl[0], "echo") == 0 || ft_strcmp(tabl[0], "export") == 0 \
	|| ft_strcmp(tabl[0], "env") == 0 || ft_strcmp(tabl[0], "exit") == 0)
	{
		if (ft_strcmp(tabl[0], "echo") == 0)
			ft_echo(tabl, var_env);
		if (ft_strcmp(tabl[0], "export") == 0 && tabl[1])
		{
			check_doublons_cl(tabl, NULL, NULL, 0);
			set_env(tabl, var_env, cmd, j);
			reset_cmd_path(var_env, cmd);
		}
		else if (ft_strcmp(tabl[0], "export") == 0 && cmd->cmd_rv != 1)
			print_sorted_env(var_env, cmd);
		if (ft_strcmp(tabl[0], "env") == 0)
			print_env(var_env, cmd);
		if (ft_strcmp(tabl[0], "exit") == 0)
			ft_exit(tabl, cmd);
	}
	else
		set_args(tabl, cmd->path, cmd, j);
}

int	tabl_is_null(int *j, char **tabl, t_command *cmd)
{
	*j = 0;
	if (tabl[0] == NULL)
	{
		cmd->cmd_rv = 0;
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
		printf("rv %d\n", cmd->cmd_rv);
		printf("%d : Command not found\n", cmd->cmd_rv);
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
		ft_pwd(tabl, cmd);
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
		set_args(tabl, cmd->path, cmd, j);
	handle_cmd_rv(tabl, cmd);
	return (0);
}

int		go_pipe(char **one, t_fd *f, t_list *var_env, t_command *cmd,
char **env)
{
	pid_t	pid;
	int		pipe_fd[2];
	int		status;

	if (f->save_pipe[0] == NULL)
	{
		go_instruction(end_redir(one, f), var_env, cmd, env);
		free_tabtab(f->save_pipe);
		return ;
	}
	pipe(pipe_fd);
	if ((pid = fork()) == -1)
		exit(1);
	else if (pid == 0)
	{
		close(pipe_fd[0]);
		dup2(pipe_fd[1], 1);
		go_instruction(end_redir(one, f), var_env, cmd, env);
		close(pipe_fd[1]);
		exit(status);
	}
	waitpid(-1, &status, 0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	go_instruction(end_redir(f->save_pipe, f), var_env, cmd, env);
	close(pipe_fd[0]);
	free_tabtab(one);
}

int check_valid_res_bis(char **str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "|") == 0 || ft_strcmp(str[i], "<") == 0 || ft_strcmp(str[i], ">") == 0 || ft_strcmp(str[i], ">>") == 0)
		{
			if (!str[i + 1])
				return (1);
			else if (ft_strcmp(str[i + 1], "|") == 0 || ft_strcmp(str[i + 1], "<") == 0 || ft_strcmp(str[i + 1], ">") == 0 || ft_strcmp(str[i + 1], ">>") == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int check_valid_res(char **str)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (check_valid_res_bis(str))
		return (1);
	while (str[i])
	{
		if (ft_is_fail_char(str[i]))
			j++;
		i++;
	}
	if (j == i)
		return (1);
	else
		return (0);
}

int		redir_and_send(t_fd *f, t_list *var_env, t_command *cmd, char **env)
{
	g_sig.boolean = 1;
	if ((chrtabtab(f->res, "|") == -1 || chrtabtab(f->first_res, "\\|") != -1) && \
	(chrtabtab(f->res, ">") == -1 || chrtabtab(f->first_res, "\\>") != -1) && \
	(chrtabtab(f->res, "<") == -1 || chrtabtab(f->first_res, "\\<") != -1) && \
	(chrtabtab(f->res, ">>") == -1 || chrtabtab(f->first_res, "\\>>") != -1))
		return (go_instruction(copy_tabtab(f->res), var_env, cmd, env));
	else if (check_valid_res(f->res))
	{
		// free_tabtab(f->res);
		//maybe return null in go instruction pour signal d'erreur
		ft_putstr_fd("bash: synthax error near unexpected token 'newline'\n", 2);
		return (2);
	}
	else if (chrtabtab(f->res, "|") == -1 || chrtabtab(f->first_res, "\\|") != -1)
		return (go_instruction(end_redir(f->res, f), var_env, cmd, env));
	else
	{
		if (count_pipes(f->res) == 1)
			return (go_pipe(divide_pipe(f), f, var_env, cmd, env));
		else
			return (handle_multipipes(f, var_env, cmd, env));
	}
	free_tabtab(f->res);
	return (2);
}
