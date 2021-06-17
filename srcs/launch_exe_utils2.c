/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exe_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:20:43 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/17 15:06:41 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	launch_exe_error(char *str, char *path, char **env, t_command *cmd)
{
	if (errno)
	{
		ft_putstr_fd(strerror(errno), 2);
		ft_putstr_fd("\n", 2);
	}
	else
		launch_exe(str, path, env, cmd);
}