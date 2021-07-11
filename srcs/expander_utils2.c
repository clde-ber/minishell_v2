/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:32:07 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/11 10:18:18 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	condition_dq(int i, int len, char *str)
{
	if (i < len && (((i == 0 && str[i] == '\"') || ((i && str[i - 1] \
		!= '\\' && str[i] == '\"')))) && (str[i + 1] != '\"'))
		return (1);
	return (0);
}

int	condition_sq(int i, int len, char *str)
{
	if (i < len && (((i == 0 && str[i] == '\'') || ((i && str[i - 1] \
		!= '\\' && str[i] == '\'')))) && (str[i + 1] != '\''))
		return (1);
	return (0);
}

void	init_vars_get_env_v(int *i, char **ret)
{
	*i = 0;
	*ret = NULL;
}

int	condition_one(int i, char *dest, char *str, char *env)
{
	if (i < (int)ft_strlen(dest) && (((i && dest[i - 1] != '\\') || i == 0) && \
		((((str[0] == '$' && (!(ft_strchr(env, '\"')))) || str[0] != '$') && \
		(dest[i] == '\"' && dest[ft_strlen(dest) - 1 - i] != '\"')) || \
		(((str[0] == '$' && (!(ft_strchr(env, '\'')))) || str[0] != '$') && \
		(dest[i] == '\'' && dest[ft_strlen(dest) - 1 - i] != '\'')))))
		return (1);
	if (i < (int)ft_strlen(dest) && (((i && dest[i - 1] != '\\' && i != \
		(int)ft_strlen(dest) - 1)) && ((dest[i] == '\'' && dest[i - 1] != '\\') \
		|| (dest[i] == '\"' && dest[i - 1] != '\\'))))
		return (1);
	return (0);
}

int	is_escaped_char(int i, char *dest)
{
	if (i < (int)ft_strlen(dest) && ((dest[i] == '\\' && (dest[i + 1] == '\\' \
		|| dest[i + 1] == '|' || dest[i + 1] == ';' || dest[i + 1] == '>' \
		|| dest[i + 1] == '<' || dest[i + 1] == '\'' || dest[i + 1] == '\"' \
		|| dest[i + 1] == '$' || ft_isspace(dest[i + 1])))))
		return (1);
	return (0);
}
