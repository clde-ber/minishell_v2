/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:54:50 by clde-ber          #+#    #+#             */
/*   Updated: 2021/04/28 14:12:21 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Functions that output a two dimensional array for environment values, sort it
** and print it.
*/

#include "minishell.h"

char	**fill_list(t_list *environ, char **list, int i)
{
	while (environ->next)
		environ = environ->next;
	while (environ->prec)
	{
		environ = environ->prec;
		i++;
	}
	if (!(list = malloc(sizeof(char *) * (i + 3))))
		return (0);
	i = 0;
	while (environ)
	{
		if (ft_strlen(environ->name))
		{
			list[i] = join_a_free(join_a_free(join_a_free(join_a_free(
ft_strjoin("declare -x ", environ->name), "="), "\""), environ->value), "\"");
			i++;
		}
		environ = environ->next;
	}
	list[i] = NULL;
	return (list);
}

char	**sort_list(char **list, int i, int j)
{
	char *tmp;
	char *i_name;
	char *j_name;

	tmp = NULL;
	i_name = NULL;
	j_name = NULL;
	while (list[++i])
	{
		while (list[++j])
		{
			i_name = ft_get_name(list[i]);
			j_name = ft_get_name(list[j]);
			if (strcmp(i_name, j_name) < 0)
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
			free(i_name);
			free(j_name);
		}
		j = 0;
	}
	return (list);
}

void	print_sorted_env(t_list *environ)
{
	char	**list;
	int		i;
	int		j;

	list = NULL;
	i = -1;
	j = -1;
	list = fill_list(environ, list, i);
	list = sort_list(list, i, j);
	while (list[++i])
		printf("%s\n", list[i]);
	ft_free(list, i + 1);
	list = NULL;
}

int		is_valid_env_name(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (!(str[i] == '_' || ft_isalnum(str[i])))
			return (0);
		i++;
	}
	return (1);
}

int		is_valid_env_name_c(char c)
{
	if (!(c == '_' || ft_isalnum(c)))
		return (0);
	return (1);
}
