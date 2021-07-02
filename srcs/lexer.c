/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:31 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Functions that play the role of the lexer & the tokenizer. It splits the
** command line string into words according to whether there is any types of
** spacing. It may also sparate words according to whether there are into
** quotes, even if no spacing, and whether there are >> > < $ ? | characters.
** It returns a two dimensional array to be used by expander functions. Each
** word in that array comes with some identifiers - for example $ ' " - that
** help binding it with its value.
*/

size_t	parse_command(size_t i, char *str, int *res, char *charset)
{
	if (is_symbol(str[i], str[i + 1]) && (i == 0 || (i && str[i - 1] != '\\')))
	{
		*res = 1;
		while (str[i] && is_symbol(str[i], str[i + 1]))
			i += is_symbol(str[i], str[i + 1]);
		i--;
	}
	else if ((((i && str[i - 1] != '\\') || !i) && str[i] == '\'') && ++i)
		while (i < ft_strlen(str) && !(str[i - 1] != '\\' && str[i] == '\''))
			i++;
	else if ((((i && str[i - 1] != '\\') || !i) && str[i] == '\"') && ++i)
		while (i < ft_strlen(str) && !(str[i - 1] != '\\' && str[i] == '\"'))
			i++;
	else if (((!i && ft_ischarset(charset, str[i])) || (i && \
	ft_ischarset(charset, str[i]) && str[i - 1] != '\\')))
	{
		*res = 1;
		i--;
	}
	else if (str[i + 1] && (is_symbol(str[i + 1], str[i + 2]) == 1 \
	|| is_symbol(str[i + 1], str[i + 2]) == 2) && (str[i] != '\\'))
		*res = 1;
	return (i);
}

size_t	len_wd(char *str, char *charset)
{
	size_t	i;
	int		res;

	res = 0;
	i = 0;
	while (i < ft_strlen(str) && res == 0)
	{
		i = parse_command(i, str, &res, charset);
		i++;
	}
	if (i >= ft_strlen(str))
		return (ft_strlen(str));
	return (i);
}

size_t	count_malloc(char *s, char *str)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (s[i] == '\0')
		return (1);
	while (i < ft_strlen(s))
	{
		while (s[i] && ft_ischarset(str, s[i]) == 0)
		{
			i += len_wd(&s[i], str);
			count++;
		}
		i++;
	}
	return (count);
}

void	init_vars_ft_split(size_t *i, size_t *j)
{
	*i = -1;
	*j = 0;
}

char	**ft_split(char *s, char *str)
{
	size_t	i;
	size_t	j;
	char	**res;

	init_vars_ft_split(&i, &j);
	if (!s || !*s)
		return ((char **)ft_calloc(2, sizeof(char *)));
	res = malloc(sizeof(char *) * (count_malloc(s, str) + 1));
	if (!(res))
		return (0);
	while (++i < ft_strlen((char *)s))
	{
		while (is_not_charset(s, j, str, i))
		{
			res[j] = malloc(sizeof(char) * (len_wd(&s[i], str) + 1));
			if (!(res[j]))
				return (ft_free(res, j));
			res[j] = ft_memmove(res[j], &s[i], len_wd(&s[i], str));
			res[j][len_wd(&s[i], str)] = '\0';
			j++;
			i += len_wd(&s[i], str);
		}
	}
	res[count_malloc(s, str)] = 0;
	return (res);
}
