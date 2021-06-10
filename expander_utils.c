/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:15 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/10 15:18:11 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Functions that replace any occurences of $ with existing environment
** variable name.
*/

void	join_string_value(char **str, char **tmp, char *trim, int *index)
{
	*str = get_string_value(trim);
	*tmp = join_a_free(*tmp, *str);
	*index += ft_strlen(*str);
}

void	init_vars_replace_by_env(size_t *i, char **tmp, char **str)
{
	*i = 0;
	*tmp = ft_strdup("");
	*str = NULL;
}

int	is_not_env_value(size_t i, char *trim)
{
	if (!(((i && trim[i] == '$' && trim[i - 1] != '\\') \
	|| (i == 0 && trim[i] == '$'))))
		return (1);
	return (0);
}

char	*replace_by_env(char *trim, t_list *var_env, t_command *cmd)
{
	size_t	i;
	char	*tmp;
	char	*str;

	init_vars_replace_by_env(&i, &tmp, &str);
	if (ft_strlen(trim) == 1 && trim[0] == '$')
	{
		ft_free_2_strings(trim, tmp);
		return (ft_strdup("$"));
	}
	while (i < ft_strlen(trim))
	{
		if ((is_not_env_value(i, trim)))
			break ;
		else
		{
			tmp = ft_strjoin_free(tmp, get_env_value(&trim[i + 1],
						var_env, cmd));
			i += cmd->index;
		}
		cmd->index = 0;
	}
	free_string(trim);
	return (antislashes_dolls(tmp));
}

char	*replace_by_env_value(char *trim, t_list *var_env, t_command *cmd)
{
	size_t	i;
	char	*tmp;
	char	*str;

	init_vars_replace_by_env(&i, &tmp, &str);
	if (ft_strlen(trim) == 1 && trim[0] == '$')
	{
		ft_free_2_strings(trim, tmp);
		return (ft_strdup("$"));
	}
	while (i < ft_strlen(trim))
	{
		if ((is_not_env_value(i, trim)))
		{
			join_string_value(&str, &tmp, &trim[i], &cmd->index);
			free(str);
		}
		else
			tmp = ft_strjoin_free(tmp, get_env_value(&trim[i + 1], \
			var_env, cmd));
		i += cmd->index;
		cmd->index = 0;
	}
	free_string(trim);
	return (antislashes_dolls(tmp));
}

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

void	init_var_nh_cmd(int *boolean, int *index, int *bool2)
{
	*boolean = 0;
	*index = 0;
	*bool2 = 0;
}

void	ft_free_nh_cmd(char *tmp, char *tmp_sub)
{
	free_string(tmp);
	free_string(tmp_sub);
}

char	*non_handled_commands(char *res, t_list *var_env, t_command *cmd)
{
	char	*tmp;
	char	*tmp_sub;
	int		boolean;
	int		bool2;
	char	*buf;

	init_var_nh_cmd(&boolean, &cmd->index, &bool2);
	tmp = ft_strdup(res);
	tmp_sub = trim_dq(&bool2, tmp);
	buf = trim_sq(&boolean, tmp_sub);
	if ((boolean == 0 || bool2 == 1) && ft_strchr(buf, '$'))
	{
		free_string(tmp);
		tmp = ft_strtrim(buf, "\'");
		free_string(buf);
		buf = replace_by_env_value(ft_strdup(tmp), var_env, cmd);
	}
	if (buf[0] == '\'' && bool2 == 0)
	{
		free_string(buf);
		buf = ft_strtrim(tmp_sub, "\'");
	}
	ft_free_nh_cmd(tmp, tmp_sub);
	return (buf);
}

char	*handled_export(char *res, t_list *var_env, t_command *cmd)
{
	char	*str_first;
	char	*str_secd;
	char	**p_bin;
	int		quotes;
	char	*name;

	init_var_h_export(&quotes, &str_first, &str_secd, &name);
	p_bin = parse_path(res, '=');
	split_env_name_a_value(&str_first, &str_secd, p_bin, res);
	env_quotes_a_values(&str_first, &str_secd, &quotes, &name);
	free_tabtab(p_bin);
	name = replace_by_env_value(name, var_env, cmd);
	if (!(is_valid_env_name(name)) || !(ft_strcmp(str_first, "")))
	{
		cmd->cmd_rv = 1;
		free(name);
		return (export_errors(str_first, str_secd, quotes, res));
	}
	free(name);
	export_replace_by_env_value(&str_first, &str_secd, var_env, cmd);
	if (cmd->cmd_rv != 1)
		cmd->cmd_rv = 0;
	return (valid_export(str_first, str_secd, quotes, res));
}
