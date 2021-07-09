/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:36:52 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/08 16:56:33 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	remove_empty_string(char *str, int *j)
{
	if (ft_strcmp(str, "") == 0)
	{
		free(str);
		(*j)--;
	}
}

char	*write_error(char *str, t_command *cmd)
{
	ft_putstr_fd("bash: unset: '", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	cmd->cmd_rv = 1;
	return (str);
}

void	if_d_quotes_unset(char **trim, char *res, int *quotes)
{
	if (res[0] == '\"')
		*trim = ft_strtrim(res, "\"");
	else
		*trim = ft_strdup(res);
	if (ft_strlen(*trim) != ft_strlen(res))
		*quotes = 1;
}

void	if_s_quotes_unset(char *trim, char **trim2)
{
	if (trim[0] == '\'')
		*trim2 = ft_strtrim(trim, "\'");
	else
		*trim2 = ft_strdup(trim);
}

char	*handled_unset(char *res, t_list *var_env, t_command *cmd)
{
	char	*str;

	if (cmd->cmd_rv != 1)
		cmd->cmd_rv = 0;
	str = replace_by_env_value(ft_strdup(res), var_env, cmd);
	str = remove_antislashes(str);
	if (!(is_valid_env_name(str)) || ft_strchr(str, '='))
		return (write_error(str, cmd));
	return (str);
}
