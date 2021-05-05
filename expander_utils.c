/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:15 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/05 14:14:28 by clde-ber         ###   ########.fr       */
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
			tmp = ft_strjoin_free(tmp, get_env_value(&trim[i + 1], var_env, cmd));
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
	cmd->index = 0;
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

int			even_or_odd(char *str)
{
	int i;

	i = 0;
	while (str[i] && str[i] == '\'')
		i++;
	return (i);
}

char		*non_handled_commands(char *res, t_list *var_env, t_command *cmd)
{
	char	*tmp;
	char	*tmp_sub;
	int		boolean;

	boolean = 0;
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

char		*find_op(char *str)
{
	int i;
	char *ret;

	i = 0;
	ret = NULL;
	if (ft_strchr(str, '+') && ft_strchr(str, '='))
	{
		ret = ft_strchr(str, '+');
		if (ret[1] && ret[1] == '=')
			return ("+=");
		else
			return ("=");
	}
	else if (ft_strchr(str, '='))
	{
		ret = ft_strchr(str, '=');
			return ("=");
	}
	else
		return ("");
}

char		*export_errors(char *str_first, char *str_secd, int quotes, char *res)
{
	char *operator;
	
	operator = find_op(res);
	write(1, "bash: export: '", 16);
	if (quotes % 2 == 0)
		write(1, ft_strtrim(str_first, "\'"), ft_strlen(ft_strtrim(str_first, "\'")));
	else
		write(1, str_first, ft_strlen(str_first));
	write(1, operator, ft_strlen(operator));
	if (quotes == 1 || quotes == 4)
		write(1, ft_strtrim(str_secd, "\'"), ft_strlen(ft_strtrim(str_secd, "\'")));
	else
		write(1, str_secd, ft_strlen(str_secd));
	write(1, "': not a valid identifier\n", 26);
	return (NULL);
}

char		*valid_export(char *str_first, char *str_secd, int quotes, char *res)
{
	char *operator;

	operator = find_op(res);
	if (quotes % 2 == 0)
		str_first = ft_strtrim(str_first, "\'");
	if (quotes == 1 || quotes == 4)
		str_secd = ft_strtrim(str_secd, "\'");
	return (ft_strjoin_free(join_a_free(str_first, operator), str_secd));
}

void		env_quotes_a_values(char **str_first, char **str_secd, int *quotes)
{
	if (ft_strlen(*str_first) != ft_strlen(ft_strtrim(*str_first, "\"")) &&
	ft_strlen(*str_secd) == ft_strlen(ft_strtrim(*str_secd, "\"")))
		*quotes = 1;
	if (ft_strlen(*str_secd) != ft_strlen(ft_strtrim(*str_secd, "\"")) &&
	ft_strlen(*str_first) == ft_strlen(ft_strtrim(*str_first, "\"")))
		*quotes = 2;
	if (ft_strlen(*str_first) != ft_strlen(ft_strtrim(*str_first, "\"")) &&
	ft_strlen(*str_secd) != ft_strlen(ft_strtrim(*str_secd, "\"")))
		*quotes = 3;
	if (ft_strlen(*str_first) == ft_strlen(ft_strtrim(*str_first, "\"")) &&
	ft_strlen(*str_secd) == ft_strlen(ft_strtrim(*str_secd, "\"")))
		*quotes = 4;
	*str_first = ft_strtrim(*str_first, "\"");
	*str_secd = ft_strtrim(*str_secd, "\"");
}

char		*get_env_name(int quotes, char *str_first)
{
	char *name;

	name = NULL;
	if (str_first)
	{
		if (quotes % 2 == 0)
			name = ft_strtrim(str_first, "\'");
		else
			name = ft_strdup(str_first);
	}
	return (name);
}

void		split_env_name_a_value(char **str_first, char **str_secd, char **p_bin, char *res)
{
	if (ft_strchr(res, '='))
	{
		*str_first = ft_strdup(p_bin[0]);
		*str_secd = ft_strdup(&ft_strchr(res, '=')[1]);
	}
	else
	{
		*str_first = ft_strdup(res);
		*str_secd = ft_strdup("");
	}
}

void		export_replace_by_env_value(char **str_first, char **str_secd,
t_list *var_env, t_command *cmd)
{
	if (*str_first[0] != '\'')
		*str_first = replace_by_env(*str_first, var_env, cmd, 0);
	if (*str_secd[0] != '\'')
		*str_secd = replace_by_env_value(*str_secd, var_env, cmd);
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
	cmd->index = 0;
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
