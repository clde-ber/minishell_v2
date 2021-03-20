#include "minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	int i;

	i = 0;
	if (!s || !fd)
		return ;
	while (s[i])
	{
		write(fd, &s[i], 1);
		i++;
	}
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	unsigned long	l;
	char			*dest;

	i = (s) ? ft_strlen(s) : 0;
	l = 0;
	if (!s || start > i)
	{
		if (!(dest = malloc(1)))
			return (NULL);
		dest[0] = 0;
		return (dest);
	}
	if (!(dest = malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while ((l < len) && s[start])
	{
		dest[l] = s[start];
		l++;
		start++;
	}
	dest[l] = '\0';
	return (dest);
}

static int		trim_first(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (set[j] && s1[i])
	{
		while (s1[i] != set[j] && set[j])
			j++;
		if (s1[i] == set[j])
		{
			i++;
			j = 0;
		}
	}
	return (i);
}

static int		trim_last(char const *s1, char const *set, int k)
{
	int		j;

	j = 0;
	while (set[j])
	{
		while (s1[k] != set[j] && set[j])
			j++;
		if (s1[k] == set[j])
		{
			k--;
			j = 0;
		}
	}
	return (k);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*dest;

	if (!set)
		return (ft_strdup(s1));
	k = ft_strlen(s1);
	i = trim_first(s1, set);
	if (i == k)
	{
		if (!(dest = malloc(1)))
			return (NULL);
		dest[0] = '\0';
		return (dest);
	}
	j = trim_last(s1, set, k);
	dest = ft_substr((char *)s1, i, j - i + 1);
	return (dest);
}