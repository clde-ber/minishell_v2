/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:08:41 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/17 15:06:41 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	unset_cmd_path(int boolean, t_command *cmd)
{
	if (boolean == 0)
	{
		if (cmd->path)
		{
			free(cmd->path);
			cmd->path = ft_strdup("");
		}
	}
}

void	name_a_value_var(char **name, char **value, char **env, int k)
{
	*name = ft_get_name(env[k]);
	*value = ft_strdup(&ft_strchr(env[k], '=')[1]);
}

void	init_strings_set_env(t_list **tmp_new, t_list **tmp, char **name)
{
	*tmp_new = NULL;
	*tmp = NULL;
	*name = NULL;
}

void	init_vars_unset(char **name, int *i, int *boolean)
{
	*name = NULL;
	*i = 1;
	*boolean = 0;
}
