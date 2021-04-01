#include "minishell.h"

size_t	len_wd(char const *str, char *charset)
{
	size_t i;
    int boolean;

	i = 0;
    boolean = 0;
	while (i < ft_strlen((char *)str) && boolean == 0)
	{
        if (((i && str[i - 1] != '\\') || !i) && str[i] == '\'' && i < ft_strlen(str))
        {
            i++;
            while (i < ft_strlen(str) && !(str[i - 1] != '\\' && str[i] == '\''))
				i++;
			boolean = 1;
        }
        if (((i && str[i - 1] != '\\') || !i) && str[i] == '\"' && i < ft_strlen(str))
        {
            i++;
            while (i < ft_strlen(str) && !(str[i - 1] != '\\' && str[i] == '\"'))
                i++;
			boolean = 1;
        }
		if ((!i && ft_ischarset(charset, str[i])) || (i && ft_ischarset(charset, str[i]) && str[i - 1] != '\\'))
		{
			i--;
			boolean = 1;
		}
		if (i < ft_strlen(str) && str[i] == '>' && str[i + 1] == '>')
		{
			i++;
			boolean = 1;
		}
		if (i < ft_strlen(str) && str[i] != '>' && str[i + 1] == '>')
			boolean = 1;
		if (i < ft_strlen(str) && str[i] != '|' && str[i + 1] == '|')
			boolean = 1;
		i++;
	}
	return (i >= ft_strlen(str)) ? ft_strlen(str) : i;
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