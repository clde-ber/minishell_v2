/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:48:22 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_strrchr(const char *s, int c)
{
	char			to_find;
	int				i;

	i = ft_strlen((char *)s);
	to_find = c;
	while (i)
	{
		if (s[i] == to_find)
			return (i);
		i--;
	}
	if (s[i] == to_find)
		return (i);
	return (-1);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	void			*ptr;

	i = 0;
	ptr = (void *)malloc(count * size);
	if (!(ptr))
		return (0);
	while (i < count * size)
	{
		((char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;

	if (!dst && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tmp_src;
	unsigned char	*tmp_dst;

	if (!dst && !src)
		return (NULL);
	if (src <= dst)
	{
		tmp_dst = (unsigned char *)dst;
		tmp_src = (unsigned char *)src;
		while (len--)
			tmp_dst[len] = tmp_src[len];
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}

int	ft_ischarset(char *str, char c)
{
	int				i;

	i = 0;
	while (str[i])
	{
		if ((char)c == str[i])
			return (1);
		i++;
	}
	return (0);
}
