/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exe_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:20:43 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/16 15:48:56 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	opendir_error(char *path, t_command *cmd, char *str, char *path_mod)
{
	write(1, "bash: ", 6);
	write(1, path, ft_strlen(path));
	write(1, ": ", 2);
	printf("%s\n", strerror(errno));
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
		printf("%s\n", strerror(errno));
	else
		launch_exe(str, path, env, cmd);
}