/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils8.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:30:06 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/16 11:31:21 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_env_c(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '\t' || c == '\n' \
		|| c == '\r' || c == '\v' || c == '\f' || c == ' ' \
		|| c == '+' || c == '\'')
		return (1);
	return (0);
}

void	fill_string_dq(int *i, int *j, char *str, char **ret)
{
	int	len;

	len = (int)ft_strlen(str);
	if (len > 2 && str[len - 2] == '\\' && str[len - 3] == '\\')
		len = len - 2;
	(*ret)[*j] = str[*i];
	(*i)++;
	(*j)++;
	while (*i < len && (str[*i] != '\"' || (str[*i] == '\"'
				&& str[*i - 1] == '\\')))
	{
		if (!(str[*i - 1] == '\\' && str[*i] == '\\'))
		{
			(*ret)[*j] = str[*i];
			(*j)++;
		}
		(*i)++;
	}
}

void	fill_string_sq(int *i, int *j, char *str, char **ret)
{
	int	len;

	len = (int)ft_strlen(str);
	if (len > 2 && str[len - 2] == '\\' && str[len - 3] == '\\')
		len = len - 2;
	(*ret)[*j] = str[*i];
	(*i)++;
	(*j)++;
	while (*i < len && (str[*i] != '\'' || (str[*i] == '\''
				&& str[*i - 1] == '\\')))
	{
		if (!(str[*i - 1] == '\\' && str[*i] == '\\'))
		{
			(*ret)[*j] = str[*i];
			(*j)++;
		}
		(*i)++;
	}
}

void	fill_string(int *i, int *j, char *str, char **ret)
{
	(*ret)[*j] = str[*i];
	(*j)++;
	(*i)++;
}

void	init_vars_a_a_q(int *i, int *j)
{
	*i = 0;
	*j = 0;
}
