/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/03 12:59:48 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/08 16:54:48 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*ft_free_3_strings_a_return(char *str_first, char *str_secd,
char *str_third)
{
	ft_free_2_strings(str_first, str_secd);
	free_string(str_third);
	return (NULL);
}

int	is_in_sq_string(int i, char *str)
{
	int	count;

	count = 0;
	while (i >= 0)
	{
		if ((i == 0 && str[i] == '\'') || (i && str[i - 1] != '\\' && str[i] \
		== '\''))
			count++;
		i--;
	}
	return (count);
}

int	is_in_dq_string(int i, char *str)
{
	int	count;

	count = 0;
	while (i >= 0)
	{
		if ((i == 0 && str[i] == '\"') || (i && str[i - 1] != '\\' && str[i] \
		== '\"'))
			count++;
		i--;
	}
	return (count);
}
