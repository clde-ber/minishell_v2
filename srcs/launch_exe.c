/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:53 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/22 15:43:28 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Functions that search and launch an executable when first command line
** agurment begins with "./". The program reads directories and compares
** their names to the ones in path. At the end, it checks whether the
** filename is correct or exists. If the last directory can't be opened,
** it returns an error. If execve - that executes the command - returns an
** error, it prints error accordingly. If command is interrupted by a signal,
** it prints an error.
*/

void	init_vars_launch_exe(pid_t *pid, int *ret, int *status)
{
	*pid = 0;
	*ret = 0;
	*status = 0;
}

void	free_2_tabs(char **argv, char **envp)
{
	free_tabtab(envp);
	free_tabtab(argv);
}

int	launch_exe(char *path, char **env, t_command *cmd)
{
	pid_t	pid;
	int		ret;
	int		status;
	char	**argv;
	char	**envp;

	init_vars_launch_exe(&pid, &ret, &status);
	argv = arg_tab(path, env);
	envp = cmd->env;
	pid = fork();
	if (pid == 0)
	{
		ret = execve(argv[0], argv, envp);
		if (ret == -1)
			write_error_launch_exe(path);
		if (errno == 2)
			exit(127);
		if (errno == 13)
			exit(126);
		exit(status);
	}
	free_tabtab(argv);
	waitpid(-1, &status, 0);
	return ((cmd->cmd_rv = exit_status(status)));
}

void	find_exe(char *path, char **env, t_command *cmd)
{
	DIR				*dir;
	char			*str;
	struct dirent	*st_dir;
	char			*path_mod;

	init_vars_find_exe(&str, &path_mod, path, &dir);
	if (!(dir))
	{
		opendir_error(path, cmd, str, path_mod);
		return ;
	}
	st_dir = readdir(dir);
	while (st_dir)
	{
		if (ft_strcmp(st_dir->d_name, str) == 0)
		{
			launch_exe(path, env, cmd);
			break ;
		}
		st_dir = readdir(dir);
	}
	if (!(st_dir))
		launch_exe_error(path, env, cmd);
	closedir(dir);
	ft_free_2_strings(path_mod, str);
}
