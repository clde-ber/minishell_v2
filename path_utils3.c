/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 06:56:53 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/15 08:35:15 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_no_arg(t_list *var_env, t_command *cmd)
{
	char	*path;
	char	*str;

	cmd->cmd_rv = 0;
	str = search_env_name("HOME", var_env);
	if (str)
	{
		path = replace_by_env_value(ft_strdup("$HOME"), var_env, cmd);
		chdir(path);
		free_string(path);
		free_string(str);
	}
	else
		cmd->cmd_rv = 1;
}
