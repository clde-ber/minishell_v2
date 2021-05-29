/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:06:50 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/29 07:01:45 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**divide_pipe(char **res, t_fd *f)
{
	int		m;
	int		i;
	char	**tabl;

	i = 0;
	m = count_tabs(res) - chrtabtab(res, "|");
	if (!(f->save_pipe = malloc(sizeof(char *) * (m + 2))))
		return (NULL);
	if (!(tabl = malloc(sizeof(char *) * (chrtabtab(res, "|") + 2))))
		return (NULL);
	while (i < chrtabtab(res, "|"))
	{
		tabl[i] = ft_strdup(res[i]);
		i++;
	}
	tabl[i] = NULL;
	i = 0;
	while (res[chrtabtab(res, "|") + i + 1])
	{
		f->save_pipe[i] = ft_strdup(res[chrtabtab(res, "|") + i + 1]);
		i++;
	}
	f->save_pipe[i] = NULL;
	return (tabl);
}

int		go_e(char **tabl, t_list *var_env, t_command *cmd)
{
	if (ft_strcmp(tabl[0], "echo") == 0)
		ft_echo(tabl, var_env);
	else if (ft_strcmp(tabl[0], "export") == 0 && tabl[1])
	{
		check_doublons_cl(tabl, NULL, NULL, 0);
		set_env(tabl, var_env, cmd);
	}
	else if (ft_strcmp(tabl[0], "export") == 0 && (!(tabl[1])))
		print_sorted_env(var_env);
	else if (ft_strcmp(tabl[0], "env") == 0)
		print_env(var_env);
	else if (ft_strcmp(tabl[0], "exit") == 0)
		ft_exit(tabl, cmd);
	else
		set_args(tabl, cmd->path, cmd);
}

int		go_instruction(char **tabl, t_list *var_env, t_command *cmd, char **env)
{
	if (tabl == NULL)
		;
	if (ft_strcmp(tabl[0], "$?"))
	{
		if (tabl[0][0] == 'e')
			go_e(tabl, var_env, cmd);
		else if (ft_strcmp(tabl[0], "pwd") == 0)
			ft_pwd(tabl);
		else if (ft_strcmp(tabl[0], "cd") == 0 && tabl[1])
			ft_cd(tabl, var_env, cmd);
		else if (ft_strcmp(tabl[0], "cd") == 0 && !tabl[1])
			cd_no_arg(var_env, cmd);
		else if (tabl[0][0] == '.' && tabl[0][1] == '/')
			find_exe(tabl[0], env, cmd);
		else if (ft_strcmp(tabl[0], "unset") == 0 && tabl[1])
			unset(var_env, tabl);
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

int		redir_and_send(char **res, t_fd *f, t_list *var_env, t_command *cmd,
char **env)
{
	g_sig.boolean = 1;
	if (chrtabtab(res, "|") == -1 && chrtabtab(res, ">") == -1 && chrtabtab(res,
	"<") == -1 && chrtabtab(res, ">>") == -1)
		return (go_instruction(copy_tabtab(res), var_env, cmd, env));
	else if (chrtabtab(res, "|") == -1)
		return (go_instruction(end_redir(res, f), var_env, cmd, env));
	else
	{
		if (count_pipes(res) == 1)
			return (go_pipe(divide_pipe(res, f), f, var_env, cmd, env));
		else
			return (handle_multipipes(res, f, var_env, cmd, env));
	}
	free_tabtab(res);
	return (2);
}
