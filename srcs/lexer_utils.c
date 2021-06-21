/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:03:54 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/17 15:49:34 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_not_charset(char *s, int j, char *str, int i)
{
	if (i < (int)ft_strlen((char *)s) && j < (int)count_malloc(s, str) && \
		ft_ischarset(str, s[i]) == 0)
		return (1);
	return (0);
}

void	*ft_free(char **res, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}
