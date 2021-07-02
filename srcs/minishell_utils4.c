/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 15:20:47 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
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
	int		boolean;
	char	*tmp;
	char	*tmp2;

	boolean = 0;
	tmp = ft_strdup(str);
	tmp2 = ft_strdup("");
	if (!(tmp))
		return (0);
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
		if_dq_unkwn_var(&tmp, str, &boolean);
	if (boolean == 0 && (!even_or_odd(tmp) || !(even_or_odd(tmp) % 2)))
		if_string_literal(&tmp, &tmp2);
	free_string(tmp2);
	tmp2 = replace_by_env_value(ft_strdup(tmp), var_env, cmd);
	if (tmp[0] == '$' && tmp[1] != '?' && ft_strcmp(tmp2, "") == 0)
	{
		ft_free_2_strings(tmp, tmp2);
		return (1);
	}
	ft_free_2_strings(tmp, tmp2);
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
