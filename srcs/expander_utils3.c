/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:26:40 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/08 16:36:00 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_string_identifier(char *dest, int i)
{
	if ((int)ft_strlen(dest) && (((((i == 0 && dest[i] == '\'') || (i && \
	dest[i - 1] != '\\' && dest[i] == '\'')) && !(is_in_dq_string(i, dest) && \
	is_in_dq_string(i, dest) % 2)) || (((i == 0 && dest[i] == '\"') || (i && \
	dest[i - 1] != '\\' && dest[i] == '\"')) && !(is_in_sq_string(i, dest) && \
	is_in_sq_string(i, dest) % 2)))))
		return (1);
	return (0);
}

char	*remove_antislashes(char *dest)
{
	int		i;
	int		j;
	char	*res;

	init_2_vars(&i, &j);
	res = malloc(sizeof(char) * (ft_strlen(dest) + 1));
	if (!(res))
		return (0);
	while (i < (int)ft_strlen(dest))
	{
		if (i < (int)ft_strlen(dest) && is_string_identifier(dest, i))
		{
			while (dest[i] && ((dest[i] == '\'' && !(is_in_dq_string(i, dest) \
			&& is_in_dq_string(i, dest) % 2)) || (dest[i] == '\"' && \
			!(is_in_sq_string(i, dest) && is_in_sq_string(i, dest) % 2))))
				i++;
		}
		else if ((int)ft_strlen(dest) && is_escaped_char(i, dest))
			i++;
		else if ((int)ft_strlen(dest))
			fill_string(&i, &j, dest, &res);
	}
	res[j] = '\0';
	free_string(dest);
	return (res);
}
