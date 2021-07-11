/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:48:45 by user42            #+#    #+#             */
/*   Updated: 2021/07/11 10:56:04 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Functions that are similar to launch_exe ones, using execve to execute
** any command. Here, functions are supposed to handle not only the "./" one
** but any shell commands. Variable $PATHenvironment value is splited with ':'
** character to help testing different locations for our command binaries -
** for example /bin/. Execve is called with first command line argument until
** it returns correctly, that is until it finds where the command binaries are
** stored. Then it executes the command or prints an error.
*/

void	init_vars_exec(int *status, char ***env, t_command *cmd, char ***p_bin)
{
	errno = 0;
	*status = 0;
	*env = cmd->env;
	*p_bin = parse_path(cmd->path, ':');
}

int	exit_status(int status)
{
	return (status % 255);
}

int	test_shell_bin(char **tabl, char **p_bin, char **res, char **env)
{
	int		count;
	int		x;
	int		i;
	int		ret;

	ret = 0;
	i = -1;
	x = 0;
	count = 0;
	while (p_bin[++i])
	{
		x = 0;
		free(tabl[0]);
		tabl[0] = set_first_arg(p_bin[i], res[0]);
		while (tabl[x])
			x++;
		ret = execve(tabl[0], tabl, env);
		if (ret == -1)
			count++;
	}
	if (i == count)
		return (command_not_found(tabl, env, p_bin));
	return (command_found(tabl, env, p_bin));
}

int	exec_command(char **args, char **res, t_command *cmd, int j)
{
	pid_t	pid;
	int		status;
	char	**tabl;
	char	**p_bin;
	char	**env;

	init_vars_exec(&status, &env, cmd, &p_bin);
	tabl = arguments(res, j, args, cmd->path);
	pid = fork();
	if (pid == -1)
		return (exit_status(1));
	else if (pid == 0)
	{
		if (test_shell_bin(tabl, p_bin, res, env))
			exit(33151);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		free_2_tabs(tabl, p_bin);
		while (wait(NULL) >= 0)
			;
	}
	return (exit_status(status));
}

void	set_args(char **res, t_command *cmd)
{
	int		index;
	char	**args;
	int		k;
	char	**n_res;

	init_vars_set_args(&index, &k, &n_res, res);
	if (len_tab(n_res) > 1)
	{
		args = malloc(sizeof(char *) * (len_tab(n_res) + 1));
		if (!(args))
			return ;
		while (++index + 1 < len_tab(n_res))
			args[index] = ft_strdup(n_res[index + 1]);
		args[index] = NULL;
		cmd->cmd_rv = exec_command(args, n_res, cmd, len_tab(n_res));
		ft_free(args, index + 1);
		free_tabtab(n_res);
	}
	else
	{
		args = ft_calloc(2, sizeof(char *));
		cmd->cmd_rv = exec_command(args, n_res, cmd, 1);
		ft_free_set_args(args, n_res);
	}
	write_error_shell(cmd, res);
}
