/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:06:50 by budal-bi          #+#    #+#             */
/*   Updated: 2021/06/07 17:00:59 by clde-ber         ###   ########.fr       */
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
	if (!(f->save_pipe = malloc(sizeof(char *) * (m + 2))))
		return (NULL);
	if (!(tabl = malloc(sizeof(char *) * (chrtabtab(f->res, "|") + 2))))
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

int		go_e(char **tabl, t_list *var_env, t_command *cmd)
{
	if (ft_strcmp(tabl[0], "echo") == 0 || ft_strcmp(tabl[0], "export") == 0
	|| ft_strcmp(tabl[0], "env") == 0 || ft_strcmp(tabl[0], "exit") == 0)
	{
		if (ft_strcmp(tabl[0], "echo") == 0)
			ft_echo(tabl, var_env);
		if (ft_strcmp(tabl[0], "export") == 0 && tabl[1])
		{
			check_doublons_cl(tabl, NULL, NULL, 0);
			set_env(tabl, var_env, cmd);
		}
		else if (ft_strcmp(tabl[0], "export") == 0 && !tabl[1])
			print_sorted_env(var_env, cmd);
		if (ft_strcmp(tabl[0], "env") == 0)
			print_env(var_env, cmd);
		if (ft_strcmp(tabl[0], "exit") == 0)
			ft_exit(tabl, cmd);
	}
	else
		set_args(tabl, cmd->path, cmd);
}

int		go_instruction(char **tabl, t_list *var_env, t_command *cmd, char **env)
{
	if (tabl == NULL)
		;
		//error
	if (ft_strcmp(tabl[0], "$?"))
	{
		if (tabl[0][0] == 'e')
			go_e(tabl, var_env, cmd);
		else if (ft_strcmp(tabl[0], "pwd") == 0)
			ft_pwd(tabl, cmd);
		else if (ft_strcmp(tabl[0], "cd") == 0 && tabl[1] && ft_strcmp(tabl[1], ""))
			ft_cd(tabl, var_env, cmd);
		else if (ft_strcmp(tabl[0], "cd") == 0 && (!tabl[1] ||
		ft_strcmp(tabl[1], "") == 0))
			cd_no_arg(var_env, cmd);
		else if (tabl[0][0] == '.' && tabl[0][1] == '/')
			find_exe(tabl[0], env, cmd);
		else if (ft_strcmp(tabl[0], "unset") == 0 && tabl[1])
			unset(var_env, tabl, cmd);
		else if (ft_strcmp(tabl[0], "unset") == 0)
			errors(cmd);
		else
			set_args(tabl, cmd->path, cmd);
	}
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
	// waitpid(-1, &status, 0);
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
	if (chrtabtab(f->res, "|") == -1 && chrtabtab(f->res, ">") == -1 && chrtabtab(f->res,
	"<") == -1 && chrtabtab(f->res, ">>") == -1)
		return (go_instruction(copy_tabtab(f->res), var_env, cmd, env));
	else if (check_valid_res(f->res))
	{
		// free_tabtab(f->res);
		//maybe return null in go instruction pour signal d'erreur
		ft_putstr_fd("Error synthax\n", 2);
		return (2);
	}
	else if (chrtabtab(f->res, "|") == -1)
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
