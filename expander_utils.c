/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:15 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/21 03:29:19 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Functions that replace any occurences of $ with existing environment
** variable name.
*/

void		join_string_value(char **str, char **tmp, char *trim, int *index)
{
	*str = get_string_value(trim);
	*tmp = join_a_free(*tmp, *str);
	*index += ft_strlen(*str);
}

char		*replace_by_env(char *trim, t_list *var_env, t_command *cmd,
		int boolean)
{
	size_t	i;
	char	*tmp;
	char	*str;

	i = 0;
	tmp = ft_strdup("");
	str = NULL;
	while (i < ft_strlen(trim))
	{
		if (is_valid_env_c(trim[i]) && (boolean = 1))
		{
			join_string_value(&str, &tmp, &trim[i], &cmd->index);
			i += ft_strlen(str);
			free(str);
		}
		else if (trim[i] == '$')
		{
			tmp = ft_strjoin_free(tmp, get_env_value(&trim[i + 1],
			var_env, cmd));
			i += cmd->index + 1;
		}
		cmd->index = 0;
	}
	free(trim);
	return (tmp);
}

char		*replace_by_env_value(char *trim, t_list *var_env, t_command *cmd)
{
	size_t	i;
	char	*tmp;
	char	*str;

	i = 0;
	tmp = ft_strdup("");
	str = NULL;
	while (i < ft_strlen(trim))
	{
		if (trim[i] != '$')
		{
			join_string_value(&str, &tmp, &trim[i], &cmd->index);
			i += ft_strlen(str);
			free(str);
		}
		else
		{
			tmp = ft_strjoin_free(tmp, get_env_value(&trim[i + 1],
						var_env, cmd));
			i += cmd->index + 1;
		}
		cmd->index = 0;
	}
	free(trim);
	return (tmp);
}

char		*non_handled_commands(char *res, t_list *var_env, t_command *cmd)
{
	char	*tmp;
	char	*tmp_sub;
	int		boolean;
	char	*buf;

	boolean = 0;
	cmd->index = 0;
	tmp = ft_strdup(res);
	if (even_or_odd(tmp) && even_or_odd(tmp) % 2)
		boolean = 1;
	tmp_sub = ft_strtrim(tmp, "\"");
	free(tmp);
	buf = ft_strdup(tmp_sub);
	free(tmp_sub);
	if (boolean == 0 && ft_strchr(buf, '$'))
		tmp_sub = replace_by_env_value(ft_strtrim(buf, "\'"), var_env, cmd);
	tmp_sub = ft_strtrim(buf, "\'");
	free(buf);
	return (tmp_sub);
}

char		*handled_export(char *res, t_list *var_env, t_command *cmd)
{
	char	*str_first;
	char	*str_secd;
	char	**p_bin;
	int		quotes;
	char	*name;

	quotes = 0;
	str_first = NULL;
	str_secd = NULL;
	if (ft_strchr(res, '+'))
		p_bin = parse_path(res, '+');
	else
		p_bin = parse_path(res, '=');
	split_env_name_a_value(&str_first, &str_secd, p_bin, res);
	env_quotes_a_values(&str_first, &str_secd, &quotes);
	if (!(name = get_env_name(quotes, str_first)))
		str_first = NULL;
	free_tabtab(p_bin);
	if ((((!(str_first)) || (!(is_valid_env_name(name)))) &&
	(cmd->cmd_rv = 1)))
	{
		free(name);
		return (export_errors(str_first, str_secd, quotes, res));
	}
	free(name);
	export_replace_by_env_value(&str_first, &str_secd, var_env, cmd);
	return (valid_export(str_first, str_secd, quotes, res));
}
