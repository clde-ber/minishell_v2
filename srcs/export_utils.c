/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:21:33 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/09 07:46:12 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_values_export(char *str, char **str_first, char **str_secd)
{
	if (str && ft_strchr(str, '='))
	{
		*str_first = ft_strdup(str);
		(*str_first)[ft_strchr_bis(str, '=')] = '\0';
		*str_secd = ft_strdup(&str[ft_strchr_bis(str, '=')]);
	}
	else
	{
		*str_first = ft_strdup(str);
		*str_secd = ft_strdup("");
	}
}

char	*handled_export(char *res, t_list *var_env, t_command *cmd)
{
	char	*str_first;
	char	*str_secd;
	char	*str;

	str = replace_by_env_value(ft_strdup(res), var_env, cmd);
	str = remove_antislashes(str);
	set_values_export(str, &str_first, &str_secd);
	if ((str_first && !(is_valid_env_name(str_first))))
	{
		if (is_unknown_env_variable(res, var_env, cmd) && !ft_strchr(res, '='))
			return (ft_free_3_strings_a_return(str_first, str_secd, str));
		cmd->cmd_rv = 1;
		return (export_errors(str_first, str_secd, str));
	}
	if (cmd->cmd_rv != 1)
		cmd->cmd_rv = 0;
	return (valid_export(str_first, str_secd, str));
}
