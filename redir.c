/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:06:50 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/25 17:53:21 by budal-bi         ###   ########.fr       */
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
	else if (tabl[0][0] == 'e')
		go_e(tabl, var_env, cmd);
	else if (ft_strcmp(tabl[0], "pwd") == 0)
		ft_pwd(tabl);
	else if (ft_strcmp(tabl[0], "cd") == 0)
		ft_cd(tabl, var_env);
	else if (tabl[0][0] == '.' && tabl[0][1] == '/')
		find_exe(tabl[0], env, cmd);
	else if (ft_strcmp(tabl[0], "unset") == 0 && tabl[1])
		unset(var_env, tabl);
	else if (ft_strcmp(tabl[0], "unset") == 0)
		errors(cmd);
	else if (ft_strcmp(tabl[0], "$?") == 0)
	{
		printf("%d : Command not found\n", cmd->cmd_rv);
		cmd->cmd_rv = 127;
	}
	else
		set_args(tabl, cmd->path, cmd);
	if (g_sig == 1)
		cmd->cmd_rv = 130;
	if (g_sig == 2)
		cmd->cmd_rv = 131;
	if (g_sig == 1 || g_sig == 2)
		g_sig = 0;
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
	waitpid(-1, &status, 0);
	close(pipe_fd[1]);
	dup2(pipe_fd[0], 0);
	go_instruction(end_redir(f->save_pipe, f), var_env, cmd, env);
	close(pipe_fd[0]);
	free_tabtab(one);
}

int		redir_and_send(t_fd *f, t_list *var_env, t_command *cmd, char **env)
{
	if (chrtabtab(f->res, "|") == -1 && chrtabtab(f->res, ">") == -1 && chrtabtab(f->res,
	"<") == -1 && chrtabtab(f->res, ">>") == -1)
		return (go_instruction(copy_tabtab(f->res), var_env, cmd, env));
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
