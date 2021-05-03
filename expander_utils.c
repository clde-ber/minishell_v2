/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:15 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/03 09:09:06 by clde-ber         ###   ########.fr       */
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

char		*handled_export(char *res, t_list *var_env, t_command *cmd)
{
	int		i;
	int		j;
	int		count;
	char	*trim_first;
	char	*trim_secd;
	char	*str_first;
	char	*str_secd;
	char	*name;
	char	*trim_cmp;
	char	*str;
	char	**p_bin;
	char	*operator;
	int		bool1;
	int		bool2;

	bool1 = 0;
	bool2 = 0;
	operator = NULL;
	str = NULL;
	i = 0;
	j = 0;
	count = 0;
	trim_first = NULL;
	trim_secd = NULL;
	str_first = NULL;
	str_secd = NULL;
	name = NULL;
	trim_cmp = NULL;
	p_bin = parse_path(res, '=');
	while (p_bin[i])
		i++;
	if (ft_strchr(res, '='))
	{
		str_first = ft_strdup(p_bin[0]);
		str_secd = ft_strdup(&ft_strchr(res, '=')[1]);
	}
	else
	{
		str_first = ft_strdup(res);
		str_secd = ft_strdup("");
	}
	if (ft_strlen(str_first) != ft_strlen(ft_strtrim(str_first, "\"")))
		bool1 = 1;
	if (ft_strlen(str_secd) != ft_strlen(ft_strtrim(str_secd, "\"")))
		bool2 = 1;
	trim_first = ft_strtrim(str_first, "\"");
	trim_secd = ft_strtrim(str_secd, "\"");
	if (trim_first[0] != '\'')
		trim_first = replace_by_env(trim_first, var_env, cmd, 0);
	if (trim_secd[0] != '\'')
		trim_secd = replace_by_env_value(trim_secd, var_env, cmd);
	if (trim_first)
	{
		if (bool1 == 0)
			trim_cmp = ft_strtrim(trim_first, "\'");
		else
			trim_cmp = ft_strdup(trim_first);
		name = ft_get_name(trim_cmp);
	}
	if ((!(trim_first)) || (!(is_valid_env_name(name))))
	{
		if (trim_first)
		{
			free(name);
			free(trim_cmp);
		}
		while (((str = ft_strtrim(res, "\'")) && (is_valid_env_name_c(str[j])
		|| (j == 0 && str[j] == '$'))))
		{
			j++;
			free(str);
		}
		operator = find_op(res);
		write(1, "bash: export: '", 16);
		if (bool1 == 0)
			write(1, ft_strtrim(trim_first, "\'"), ft_strlen(ft_strtrim(trim_first, "\'")));
		else
			write(1, trim_first, ft_strlen(trim_first));
		write(1, operator, ft_strlen(operator));
		if (bool2 == 0)
			write(1, ft_strtrim(trim_secd, "\'"), ft_strlen(ft_strtrim(trim_secd, "\'")));
		else
			write(1, trim_secd, ft_strlen(trim_secd));
		write(1, "': not a valid identifier\n", 26);
		cmd->cmd_rv = 1;
		free(trim_secd);
		free(str_first);
		free(str_secd);
		free(str);
		free(trim_first);
		ft_free(p_bin, i + 1);
		return (NULL);
	}
	free(str_first);
	free(str_secd);
	if (bool1 == 0)
		str_first = ft_strtrim(trim_first, "\'");
	else
		str_first = ft_strdup(trim_first);
	if (bool2 == 0)
		str_secd = ft_strtrim(trim_secd, "\'");
	else
		str_secd = ft_strdup(trim_secd);
	free(trim_first);
	free(trim_secd);
	free(name);
	free(trim_cmp);
	ft_free(p_bin, i + 1);
	return (ft_strjoin_free(join_a_free(str_first, "="), str_secd));
}
