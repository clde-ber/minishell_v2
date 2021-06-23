/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:56:17 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/23 06:23:40 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Functions that ouput a two dimensional array from a string with a single
** character as separator. Useful for getting all possible locations for shell
** command binaries.
*/

static size_t	len_word(char *str, int c)
{
	size_t	i;

	i = 0;
	while (i < ft_strlen(str))
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] && str[i] != '\"')
				i++;
		}
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

void	is_part_of_string(char c, char *s, size_t *i)
{
	(*i)++;
	while (s[*i] && s[*i] != c)
		(*i)++;
}

static size_t	count_tab(char *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s[i] == '\0' || c == '\0')
		return (1);
	while (i < ft_strlen(s))
	{
		if (i < ft_strlen(s) && s[i] == '\'' && s[i + 1])
			is_part_of_string(s[i], s, &i);
		if (i < ft_strlen(s) && s[i] == '\"' && s[i + 1])
			is_part_of_string(s[i], s, &i);
		if (i < ft_strlen(s) && s[i] && s[i] != c && (s[i + 1] == c \
		|| s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void	*free_path(char **res, int j)
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

char	**parse_path(char *s, char c)
{
	size_t	i;
	size_t	j;
	char	**res;

	init_vars_ft_split(&i, &j);
	if (!s || !*s)
		return ((char **)ft_calloc(2, sizeof(char *)));
	res = malloc(sizeof(char *) * (count_tab(s, c) + 1));
	if (!(res))
		return (0);
	while (++i < ft_strlen(s))
	{
		while (j < count_tab(s, c) && s[i] && s[i] != c)
		{
			res[j] = malloc(sizeof(char) * (len_word(&s[i], c) + 1));
			if (!(res[j]))
				return (free_path(res, j));
			res[j] = ft_memmove(res[j], &s[i], len_word(&s[i], c));
			res[j][len_word(&s[i], c)] = '\0';
			j++;
			i += len_word(&s[i], c);
		}
	}
	res[count_tab(s, c)] = 0;
	return (res);
}
