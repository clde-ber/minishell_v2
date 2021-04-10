#include "minishell.h"

size_t	ft_strlen(char *str)
{
	size_t i;

	i = 0;
	// ft_putstr_fd(str, 1);
	// write(1, "ping", 4);
	while (str[i])
	{
		// ft_putstr_nbr((int)i, 1);
		// write(1, &str[i], 1);
		i++;
	}
	// ft_putstr_nbr(i, 1);
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
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
	return (ptr);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t i;

	i = 0;
	while (s1[i] || s2[i])
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str && *str != (char)c)
		str++;
	return (*str == c ? str : NULL);
}

char	*ft_strdup(const char *s1)
{
	size_t	i;
	char	*ptr;

	i = 0;
	// write(1, "00", 2);
	// ft_putstr_fd(s1, 1);
	size_t j = ft_strlen(s1);
	// ft_putstr_nbr(j, 1);
	if (!(ptr = malloc(sizeof(char) * (ft_strlen((char *)s1) + 1))))
		return (0);
	// write(1, "11", 2);
	while (s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	// write(1, "22", 2);
	ptr[i] = '\0';
	// write(1, "33", 2);
	return (ptr);
}

