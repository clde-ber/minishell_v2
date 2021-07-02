/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exe_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:20:43 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	child_process(char **argv, char **envp, char *path, int *ret)
{
	*ret = execve(argv[0], argv, envp);
	if (*ret == -1)
		write_error_launch_exe(path);
}

void	opendir_error(char *path, t_command *cmd, char *str, char *path_mod)
{
	ft_putstr_fd("bash: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(strerror(errno), 2);
	ft_putstr_fd("\n", 2);
	cmd->cmd_rv = 127;
	free_string(str);
	free_string(path_mod);
}

void	init_vars_find_exe(char **str, char **path_mod, char *path,
DIR **dir)
{
	*str = ft_get_filename(path, '/');
	*path_mod = get_path(path, '/');
	*dir = opendir(*path_mod);
	errno = 0;
}

void	launch_exe_error(char *path, char **env, t_command *cmd)
{
	if (errno)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
		launch_exe(path, env, cmd);
}
