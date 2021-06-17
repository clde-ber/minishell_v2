/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_a_env.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:15 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/17 15:06:41 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Functions that replace any occurences of $ with existing environment
** variable name.
*/

char	*replace_by_env(char *res, char *trim, t_list *var_env, t_command *cmd)
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
		if ((is_not_env_value(i, trim)) && ft_strchr(res, '=') == 0)
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

char	*replace_by_env_value_no_space(char *trim, t_list *var_env,
t_command *cmd)
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
	return (is_it_unknown_var(tmp));
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

char	*non_handled_commands(char *res, t_list *var_env, t_command *cmd)
{
	char	*tmp;
	char	*tmp_sub;
	int		boolean;
	int		bool2;
	char	*buf;

	init_var_nh_cmd(&boolean, &cmd->index, &bool2, &cmd->bol);
	tmp = ft_strdup(res);
	tmp_sub = trim_dq(&bool2, tmp);
	buf = trim_sq(&boolean, tmp_sub);
	if ((boolean == 0 || bool2 == 1) && ft_strchr(buf, '$'))
	{
		free_string(tmp);
		if (bool2 == 0)
			tmp = ft_strtrim(buf, "\'");
		else
			tmp = ft_strdup(buf);
		free_string(buf);
		if (bool2 == 1)
			buf = no_trim_starting_space(tmp, var_env, cmd);
		else
			buf = replace_by_env_value_no_space(ft_strdup(tmp), var_env, cmd);
	}
	trim_s_quotes(&buf, tmp_sub, bool2, tmp);
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
	if ((name && !(is_valid_env_name(name)) && ft_strchr(res, '=')) || \
	!(ft_strcmp(name, "")) && !(is_unknown_env_variable(res, var_env, cmd)))
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
