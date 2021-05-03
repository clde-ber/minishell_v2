/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:15 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/03 11:39:18 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Functions that replace any occurences of $ with existing environment
** variable name.
*/

char		*replace_by_env(char *trim, t_list *var_env, t_command *cmd,
		int boolean)
{
	size_t	i;
	char	*tmp;
	char	*str;

	i = 0;
	tmp = ft_strdup("");
	cmd->index = 0;
	if (trim[0] == '\'')
	{
		str = join_a_free(tmp, trim);
		tmp = ft_strtrim(str, "\'");
		free(str);
		return (tmp);
	}
	while (i < ft_strlen(trim))
	{
		if (is_valid_env_c(trim[i]))
		{
			str = get_string(&trim[i]);
			tmp = join_a_free(tmp, str);
			cmd->index += ft_strlen(str);
			i += ft_strlen(str);
			free(str);
			boolean = 1;
		}
		else if (trim[i] == '$')
		{
			tmp = ft_strjoin_free(tmp, get_env(&trim[i + 1], var_env, cmd));
			i += cmd->index + 1;
		}
		else
		{
			free(tmp);
			free(trim);
			return (NULL);
		}
		cmd->index = 0;
	}
	if (boolean == 0)
	{
		errors(cmd);
		free(tmp);
		free(trim);
		return (NULL);
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
	cmd->index = 0;
	if (trim[0] == '\'')
	{
		str = ft_strjoin_free(tmp, trim);
		tmp = ft_strtrim(str, "\'");
		free(str);
		return (tmp);
	}
	while (i < ft_strlen(trim))
	{
		if (trim[i] != '$')
		{
			str = get_string_value(&trim[i]);
			tmp = join_a_free(tmp, str);
			cmd->index += ft_strlen(str);
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
	char	*ret;

	tmp = ft_strdup(res);
	tmp_sub = ft_strtrim(tmp, "\"");
	ret = NULL;
	free(tmp);
	if (ft_strchr(tmp_sub, '$'))
		tmp_sub = replace_by_env_value(tmp_sub, var_env, cmd);
	ret = ft_strtrim(tmp_sub, "\'");
	free(tmp_sub);
	return (ret);
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

char		*export_errors(char *str_first, char *str_secd, int bool1, int bool2, char *res)
{
	char *operator;
	
	operator = find_op(res);
	write(1, "bash: export: '", 16);
	if (bool1 == 0)
		write(1, ft_strtrim(str_first, "\'"), ft_strlen(ft_strtrim(str_first, "\'")));
	else
		write(1, str_first, ft_strlen(str_first));
	write(1, operator, ft_strlen(operator));
	if (bool2 == 0)
		write(1, ft_strtrim(str_secd, "\'"), ft_strlen(ft_strtrim(str_secd, "\'")));
	else
		write(1, str_secd, ft_strlen(str_secd));
	write(1, "': not a valid identifier\n", 26);
	return (NULL);
}

char		*valid_export(char *str_first, char *str_secd, int bool1, int bool2)
{
	if (bool1 == 0)
		str_first = ft_strtrim(str_first, "\'");
	if (bool2 == 0)
		str_secd = ft_strtrim(str_secd, "\'");
	return (ft_strjoin_free(join_a_free(str_first, "="), str_secd));}

void		env_quotes_a_values(char **str_first, char **str_secd, int *bool1, int *bool2)
{
	if (ft_strlen(*str_first) != ft_strlen(ft_strtrim(*str_first, "\"")))
		*bool1 = 1;
	if (ft_strlen(*str_secd) != ft_strlen(ft_strtrim(*str_secd, "\"")))
		*bool2 = 1;
	*str_first = ft_strtrim(*str_first, "\"");
	*str_secd = ft_strtrim(*str_secd, "\"");
}

char		*get_env_name(int bool1, char *str_first)
{
	char *name;
	char *trim_cmp;

	name = NULL;
	trim_cmp = NULL;
	if (str_first)
	{
		if (bool1 == 0)
			trim_cmp = ft_strtrim(str_first, "\'");
		else
			trim_cmp = ft_strdup(str_first);
		name = ft_get_name(trim_cmp);
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

char		*handled_export(char *res, t_list *var_env, t_command *cmd)
{
	char	*str_first;
	char	*str_secd;
	char	**p_bin;
	int		bool1;
	int		bool2;

	bool1 = 0;
	bool2 = 0;
	str_first = NULL;
	str_secd = NULL;
	p_bin = parse_path(res, '=');
	split_env_name_a_value(&str_first, &str_secd, p_bin, res);
	env_quotes_a_values(&str_first, &str_secd, &bool1, &bool2);
	if (str_first[0] != '\'')
		str_first = replace_by_env(str_first, var_env, cmd, 0);
	if (str_secd[0] != '\'')
		str_secd = replace_by_env_value(str_secd, var_env, cmd);
	if (!(get_env_name(bool1, str_first)))
		str_first = NULL;
	if ((!(str_first)) || (!(is_valid_env_name(get_env_name(bool1, str_first)))))
	{
		cmd->cmd_rv = 1;
		return (export_errors(str_first, str_secd, bool1, bool2, res));
	}
	free_tabtab(p_bin);
	return (valid_export(str_first, str_secd, bool1, bool2));
}
