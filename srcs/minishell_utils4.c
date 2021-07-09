/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:20:47 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/08 16:36:28 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_string(char *str)
{
	if (str)
		free(str);
	str = NULL;
}

void	if_string_literal(char **tmp, char **tmp2)
{
	free_string(*tmp2);
	*tmp2 = ft_strtrim(*tmp, "\'");
	free_string(*tmp);
	*tmp = ft_strdup(*tmp2);
}

void	if_dq_unkwn_var(char **tmp, char *str, int *boolean)
{
	free_string(*tmp);
	*tmp = ft_strtrim(str, "\"");
	*boolean = 1;
}

int	is_unknown_env_variable(char *str, t_list *var_env, t_command *cmd)
{
	char	*value;

	value = replace_by_env_value(ft_strdup(str), var_env, cmd);
	if ((ft_strcmp(value, str) && ft_strcmp(value, "") == 0))
	{
		free_string(value);
		return (1);
	}
	free_string(value);
	return (0);
}

void	print_tabtab(char **res)
{
	int		i;

	i = 0;
	while (res[i])
	{
		ft_putstr_fd(res[i], 2);
		i++;
	}
}
