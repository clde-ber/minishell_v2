/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:55:17 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/20 19:04:28 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_symbol(char c, char comp)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	if (c == '$' && comp == '?')
		return (2);
	return (0);
}

int		count_pipes(char **res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (res[i])
	{
		if (ft_strcmp(res[i], "|") == 0)
			j++;
		i++;
	}
	return (j);
}