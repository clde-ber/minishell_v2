#include "minishell.h"

int is_symbol(char c, char comp)
{
	if (c == '<' || c == '>' || c == '|')
		return (1);
	if (c == '$' && comp == '?')
		return (2);
	return (0);
}

size_t parse_command(int i, char *str, int *res, char *charset)
{
	if (is_symbol(str[i], str[i + 1]) && (*res = 1))
	{
		while (str[i] && is_symbol(str[i], str[i + 1]))
			i += is_symbol(str[i], str[i + 1]);
		i--;
	}
	else if ((((i && str[i - 1] != '\\') || !i) && str[i] == '\'') && (*res = 1))
	{
		i++;
    	while (i < ft_strlen(str) && !(str[i - 1] != '\\' && str[i] == '\''))
			i++;
	}
	else if ((((i && str[i - 1] != '\\') || !i) && str[i] == '\"') && (*res = 1))
    {
        i++;
        while (i < ft_strlen(str) && !(str[i - 1] != '\\' && str[i] == '\"'))
            i++;
    }
	else if (((!i && ft_ischarset(charset, str[i])) || (i &&
		ft_ischarset(charset, str[i]) && str[i - 1] != '\\')) && (*res = 1))
			i--;
	else if (str[i + 1] && (is_symbol(str[i + 1], str[i + 2]) == 1 ||
	is_symbol(str[i + 1], str[i + 2]) == 2))
		*res = 1;
	return (i);
}

size_t	len_wd(char const *str, char *charset)
{
	size_t i;
	int j;
	int res;

	j = 1;
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

size_t	count_malloc(char const *s, char *str)
{
	size_t i;
	size_t count;

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

void		*ft_free(char **res, int j)
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

char			**ft_split(char const *s, char *str)
{
	size_t	i;
	size_t	j;
	char	**res;

	i = 0;
	j = 0;
	if (!s || !*s)
		return ((char **)ft_calloc(2, sizeof(char *)));
	if (!(res = malloc(sizeof(char *) * (count_malloc(s, str) + 1))))
		return (0);
	while (i < ft_strlen((char *)s))
	{
		while (i < ft_strlen((char *)s) && j < count_malloc(s, str) && ft_ischarset(str, s[i]) == 0)
		{
			if (!(res[j] = malloc(sizeof(char) * (len_wd(&s[i], str) + 1))))
				return (ft_free(res, j));
			res[j] = ft_memmove(res[j], &s[i], len_wd(&s[i], str) + 1);
			res[j][len_wd(&s[i], str)] = '\0';
			j++;
			i += len_wd(&s[i], str);
		}
		i++;
	}
	res[count_malloc(s, str)] = 0;
	return (res);
}