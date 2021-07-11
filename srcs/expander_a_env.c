/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_a_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:15 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/11 10:25:53 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Functions that replace any occurences of $ with existing environment
** variable name.
*/

char	*replace_by_env_value_no_space(char *trim, t_list *var_env,
t_command *cmd)
{
	size_t	i;
	char	*tmp;
	char	*str;

	init_vars_replace_by_env(&i, &tmp, &str);
	while (i < ft_strlen(trim))
	{
		if (((is_not_env_value(i, trim) || ((is_in_sq_string(i, trim) \
		&& is_in_sq_string(i, trim) % 2) && !(is_in_dq_string(i, trim) && \
		is_in_dq_string(i, trim) % 2))) && (!(trim[i] == '$' && trim[i + 1] \
		== '?'))) && !((trim[i] == '$' && trim[i + 1] == '?') && \
		is_command_return_value(i, trim)))
		{
			str = get_string_value(&trim[i], 0, trim, i);
			join_string_value(&str, &tmp, &trim[i], &cmd->index);
			free(str);
		}
		else
			tmp = ft_strjoin_free(tmp, get_env_value(&trim[i + 1], \
			var_env, cmd));
		i += (size_t)cmd->index;
		cmd->index = 0;
	}
	free_string(trim);
	return (is_it_unknown_var(tmp));
}

char	*replace_by_env_value(char *trim, t_list *var_env, t_command *cmd)
{
	size_t	i;
	char	*tmp;
	char	*str;

	init_vars_replace_by_env(&i, &tmp, &str);
	while (i < ft_strlen(trim))
	{
		if (((is_not_env_value(i, trim) || ((is_in_sq_string(i, trim) \
		&& is_in_sq_string(i, trim) % 2) && !(is_in_dq_string(i, trim) && \
		is_in_dq_string(i, trim) % 2))) && (!(trim[i] == '$' && trim[i + 1] \
		== '?'))) && !((trim[i] == '$' && trim[i + 1] == '?') && \
		is_command_return_value(i, trim)))
		{
			str = get_string_value(&trim[i], 0, trim, i);
			join_string_value(&str, &tmp, &trim[i], &cmd->index);
			free(str);
		}
		else
			tmp = ft_strjoin_free(tmp, get_env_value(&trim[i + 1], \
			var_env, cmd));
		i += (size_t)cmd->index;
		cmd->index = 0;
	}
	free_string(trim);
	return (antislashes_dolls(tmp));
}

int	is_not_in_string(char *buf)
{
	if (!(buf[0] == '\"' && buf[ft_strlen(buf) - 1] == '\"'))
		return (1);
	return (0);
}

void	init_vars_nh_commands(int *is_value, char **buf, char *res)
{
	*is_value = 0;
	*buf = ft_strdup(res);
}

char	*non_handled_commands(char *res, t_list *var_env, t_command *cmd)
{
	char	*buf;
	int		is_value;
	char	*tmp;

	init_vars_nh_commands(&is_value, &buf, res);
	tmp = search_env_name(&buf[1], var_env);
	if (!(tmp))
	{
		set_buf_value(&buf, var_env, cmd);
		if (ft_strchr((const char *)buf, '$') && \
		is_command_return_value(ft_strchr_bis((const char *)buf, '$'), buf))
			is_value = 1;
		buf = remove_antislashes(buf);
		if (is_value == 1 && ft_strcmp(buf, "$?") == 0)
			buf = rv_itoa(cmd->cmd_rv, buf);
		return (buf);
	}
	free_string(tmp);
	set_buf_value(&buf, var_env, cmd);
	return (buf);
}
