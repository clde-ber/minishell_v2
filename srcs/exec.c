/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:48:45 by user42            #+#    #+#             */
/*   Updated: 2021/06/17 15:06:41 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Functions that are similar to launch_exe ones, using execve to execute
** any command. Here, functions are supposed to handle not only the "./" one
** but any shell commands. Variable $PATHenvironment value is splited with ':'
** character to help testing different locations for our command binaries -
** for example /bin/. Execve is called with first command line argument until
** it returns correctly, that is until it finds where the command binaries are
** stored. Then it executes the command or prints an error.
*/

int	exit_status(int status)
{
	return (status % 255);
}

int	test_shell_bin(char **tabl, char **p_bin, char **res, char **env)
{
	char	*str;
	int		count;
	int		x;
	int		i;
	int		ret;

	ret = 0;
	i = -1;
	x = 0;
	count = 0;
	str = NULL;
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
		return (command_not_found(tabl, env, p_bin, res));
	return (command_found(tabl, env, p_bin));
}

int	exec_command(char **args, char **res, char *path, int j)
{
	pid_t	pid;
	int		status;
	char	**tabl;
	char	**p_bin;
	char	**env;

	pid = 0;
	errno = 0;
	status = 0;
	tabl = arguments(res, j, args, path);
	p_bin = parse_path(path, ':');
	env = environment(path);
	pid = fork();
	if (pid == 0)
	{
		if (test_shell_bin(tabl, p_bin, res, env))
			exit(33151);
		exit(status);
	}
	free_tabtab(tabl);
	free_tabtab(p_bin);
	free_tabtab(env);
	waitpid(-1, &status, 0);
	return (exit_status(status));
}

int	set_args(char **res, char *path, t_command *cmd, int i)
{
	int		index;
	char	**args;
	int		k;

	init_vars_set_args(&index, &k);
	if (i > 1)
	{
		args = malloc(sizeof(char *) * i);
		if (!(args))
			return (0);
		while (++index + 1 < i)
			args[index] = ft_strdup(res[index + 1]);
		args[index] = NULL;
		cmd->cmd_rv = exec_command(args, res, path, i);
		if (cmd->cmd_rv == 127)
			write_error_shell(cmd, res);
		ft_free(args, index + 1);
		return (0);
	}
	args = ft_calloc(2, sizeof(char *));
	cmd->cmd_rv = exec_command(args, res, path, 1);
	if (cmd->cmd_rv == 127)
		write_error_shell(cmd, res);
	ft_free_set_args(args);
	return (0);
}
