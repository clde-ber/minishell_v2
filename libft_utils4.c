#include "minishell.h"

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