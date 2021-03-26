#include "minishell.h"

static size_t	len_word(char const *str, int c)
{
	size_t i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			break ;
		i++;
	}
	return (i);
}

static size_t	count_tab(char const *s, char c)
{
	size_t i;
	size_t count;

	i = 0;
	count = 0;
	if (s[i] == '\0' || c == '\0')
		return (1);
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			count++;
		i++;
	}
	return (count);
}

static void		*free_path(char **res, int j)
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

char			**parse_path(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	if (!s || !*s)
		return ((char **)ft_calloc(2, sizeof(char *)));
	if (!(res = malloc(sizeof(char *) * (count_tab(s, c) + 1))))
		return (0);
	while (i < ft_strlen(s))
	{
		while (j < count_tab(s, c) && s[i] && s[i] != c)
		{
			if (!(res[j] = malloc(sizeof(char) * (len_word(&s[i], c) + 1))))
				return (free_path(res, j));
			res[j] = ft_memmove(res[j], &s[i], len_word(&s[i], c) + 1);
			res[j][len_word(&s[i], c)] = '\0';
			j++;
			i += len_word(&s[i], c);
		}
		i++;
	}
	res[count_tab(s, c)] = 0;
	return (res);
}