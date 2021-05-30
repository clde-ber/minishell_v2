/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:15 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/29 14:17:29 by clde-ber         ###   ########.fr       */
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
	if ((even_or_odd(tmp)) && even_or_odd(tmp) % 2)
		boolean = 1;
	tmp_sub = ft_strtrim(tmp, "\"");
	free(tmp);
	buf = ft_strdup(tmp_sub);
	if (boolean == 0 && ft_strchr(buf, '$'))
	{
		tmp = ft_strtrim(buf, "\'");
		free(tmp_sub);
		tmp_sub = replace_by_env_value(tmp, var_env, cmd);
	}
	tmp = ft_strtrim(tmp_sub, "\'");
	free(tmp_sub);
	free(buf);
	return (tmp);
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
	printf("str_first %s\n", str_first);
	if (!(name = get_env_name(quotes, str_first)))
		str_first = NULL;
	free_tabtab(p_bin);
	printf("name %s\n", name);
	if ((!(str_first)) || (!(is_valid_env_name(name))) ||
	(!(ft_strcmp(str_first, ""))))
	{
		free(name);
		cmd->cmd_rv = 1;
		return (export_errors(str_first, str_secd, quotes, res));
	}
	free(name);
	export_replace_by_env_value(&str_first, &str_secd, var_env, cmd);
	if (cmd->cmd_rv != 1)
		cmd->cmd_rv = 0;
	return (valid_export(str_first, str_secd, quotes, res));
}
