/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 07:43:03 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_back(char *str, int *j)
{
	int	k;

	k = 0;
	while (*j < (int)ft_strlen(str) && (str[*j] == '/' \
	|| str[*j] == '.'))
	{
		while (str[*j] == '/')
			(*j)++;
		if (str[*j] == '.')
		{
			(*j)++;
			while (str[*j] == '.')
			{
				(*j)++;
				k++;
			}
		}
	}
	return (k);
}

void	path_copy(char **buf, int k)
{
	int	i;

	i = ft_strlen(*buf) - 1;
	while (i > 0 && k >= 0)
	{
		if ((*buf)[i] == '/')
		{
			(*buf)[i] = '\0';
			k--;
		}
		i--;
	}
}

int	count_slash(char *old_pwd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < (int)ft_strlen(old_pwd))
	{
		if (old_pwd[i] == '/')
		{
			count++;
			i++;
		}
		while (old_pwd[i] == '/')
			i++;
		i++;
	}
	return (count);
}

void	cd_go_back(int k, char **buf, char *old_pwd)
{
	if (k < count_slash(old_pwd))
		path_copy(buf, k);
	else
	{
		free(*buf);
		*buf = ft_strdup("/");
	}
}

void	cd_go_front(char *res, int *i, char **buf)
{
	int	index;
	int	count;

	count = 0;
	index = *i;
	if ((*buf)[ft_strlen(*buf) - 1] != '/')
		*buf = join_a_free(join_a_free(*buf, "/"), &res[index]);
	else
		*buf = join_a_free(*buf, &res[index]);
	while ((*buf)[count] && (*buf)[count] != '.')
		count++;
	while ((*buf)[count])
	{
		(*buf)[count] = '\0';
		count++;
	}
	while (res[*i] && res[*i] != '.')
		(*i)++;
}
