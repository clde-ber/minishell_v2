/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:36:52 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/17 15:06:41 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	remove_empty_string(char *str, int *j)
{
	if (ft_strcmp(str, "") == 0)
	{
		free(str);
		(*j)--;
	}
}

char	*write_error(char *trim, char *trim2, int quotes, t_command *cmd)
{
	char	*str;

	if (trim[0] == '\'')
		str = ft_strtrim(trim, "\'");
	else
		str = ft_strdup(trim);
	ft_putstr_fd("bash: unset: '", 2);
	if (quotes == 0)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd(trim, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	cmd->cmd_rv = 1;
	free_string(trim);
	free_string(trim2);
	free_string(str);
	return (ft_strdup(""));
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
	char	*trim;
	char	*trim2;
	int		quotes;

	init_2_strings(trim, trim2);
	init_2_vars(&quotes, &cmd->index);
	if_d_quotes_unset(&trim, res, &quotes);
	if (((quotes == 0 && ft_strchr(trim, '\"') == 0) || (quotes == 1
				&& ft_strchr(trim, '\'') == 0)) && ft_strcmp(trim, ""))
	{
		if_s_quotes_unset(trim, &trim2);
		free_string(trim);
		trim = replace_by_env_value(trim2, var_env, cmd);
	}
	trim2 = ft_strdup(trim);
	if (!(is_valid_env_name(trim)))
		return (write_error(trim, trim2, quotes, cmd));
	free_string(trim2);
	return (trim);
}