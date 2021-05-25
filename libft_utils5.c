/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:48:39 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/24 16:59:23 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		conv_char_int(char str, int k)
{
	k *= 10;
	k += str - 48;
	return (k);
}

int				ft_atoi(const char *str)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' ||
		str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j++;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		k = conv_char_int(str[i], k);
		i++;
	}
	if (j % 2 != 0)
		return (k * -1);
	return (k);
}
