/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:15 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/05 15:50:06 by clde-ber         ###   ########.fr       */
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

	boolean = 0;
	cmd->index = 0;
	tmp = ft_strdup(res);
	if (even_or_odd(tmp) && even_or_odd(tmp) % 2)
		boolean = 1;
	tmp_sub = ft_strtrim(tmp, "\"");
	free(tmp);
	if (boolean == 0 && ft_strchr(tmp_sub, '$'))
		tmp_sub = replace_by_env_value(ft_strtrim(tmp_sub, "\'"), var_env, cmd);
	tmp_sub = ft_strtrim(tmp_sub, "\'");
	return (tmp_sub);
}

char		*handled_export(char *res, t_list *var_env, t_command *cmd)
{
	char	*str_first;
	char	*str_secd;
	char	**p_bin;
	int		quotes;

	quotes = 0;
	str_first = NULL;
	str_secd = NULL;
	if (ft_strchr(res, '+'))
		p_bin = parse_path(res, '+');
	else
		p_bin = parse_path(res, '=');
	split_env_name_a_value(&str_first, &str_secd, p_bin, res);
	env_quotes_a_values(&str_first, &str_secd, &quotes);
	export_replace_by_env_value(&str_first, &str_secd, var_env, cmd);
	if (!(get_env_name(quotes, str_first)))
		str_first = NULL;
	free_tabtab(p_bin);
	if (((!(str_first)) || (!(is_valid_env_name(get_env_name(quotes,
	str_first))))) && (cmd->cmd_rv = 1))
		return (export_errors(str_first, str_secd, quotes, res));
	return (valid_export(str_first, str_secd, quotes, res));
}
