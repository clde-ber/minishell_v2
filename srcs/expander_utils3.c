/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:26:40 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/17 15:06:41 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*trim_dq(int *bool2, char *tmp)
{
	char	*tmp_sub;

	tmp_sub = NULL;
	if (tmp[0] == '\"')
	{
		*bool2 = 1;
		tmp_sub = ft_strtrim(tmp, "\"");
	}
	else
		tmp_sub = ft_strdup(tmp);
	return (tmp_sub);
}

char	*trim_sq(int *boolean, char *tmp_sub)
{
	char	*buf;

	buf = NULL;
	if ((even_or_odd(tmp_sub)) && even_or_odd(tmp_sub) % 2)
		*boolean = 1;
	buf = ft_strdup(tmp_sub);
	return (buf);
}

void	init_var_nh_cmd(int *boolean, int *index, int *bool2, int *cmd_bol)
{
	*boolean = 0;
	*index = 0;
	*bool2 = 0;
	*cmd_bol = 0;
}

void	trim_s_quotes(char **buf, char *tmp_sub, int bool2, char *tmp)
{
	if (*buf && (*buf)[0] == '\'' && bool2 == 0)
	{
		free_string(*buf);
		*buf = ft_strtrim(tmp_sub, "\'");
	}
	free_string(tmp);
	free_string(tmp_sub);
}

char	*no_trim_starting_space(char *tmp, t_list *var_env, t_command *cmd)
{
	char	*buf;

	buf = replace_by_env_value(ft_strdup(tmp), var_env, cmd);
	cmd->bol = 1;
	return (buf);
}