/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:38 by clde-ber          #+#    #+#             */
/*   Updated: 2021/04/28 13:57:07 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		find_n(char *buf, size_t size)
{
	size_t i;

	i = 0;
	while (i < size && buf[i])
	{
		if (buf[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

char	*join_a_free(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	i = -1;
	j = -1;
	if (!s1 && !s2)
		return (0);
	if (!(ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (0);
	while (s1[++i])
		ptr[i] = s1[i];
	while (s2[++j])
		ptr[i + j] = s2[j];
	ptr[i + j] = '\0';
	free(s1);
	return (ptr);
}