#include "minishell.h"

int	ft_isalnum(int c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	else if (c >= 'A' && c <= 'Z')
		return (1);
	else if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_strlcpy(char *dst, const char *src, int dstsize)
{
	int i;
	int j;

	j = 0;
	i = ft_strlen(src);
	if (!dstsize)
		return (i);
	while (j < dstsize - 1 && src[j])
	{
		dst[j] = src[j];
		j++;
	}
	if (dstsize)
		dst[j] = '\0';
	return (i);
}