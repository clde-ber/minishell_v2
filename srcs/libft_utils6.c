/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils6.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 12:28:36 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_putstr_nbr(int i, int fd)
{
	int		j;
	char	*buf;

	j = 0;
	buf = ft_itoa(i);
	while (buf[j])
	{
		write(fd, &buf[j], 1);
		j++;
	}
	free(buf);
}

static char	*ft_attrib(int n, char *res, int i)
{
	int	j;

	j = 0;
	if (n == -2147483648)
		n++;
	if (n < 0)
	{
		n *= -1;
		j = 1;
	}
	while (i >= j)
	{
		res[i] = n % 10 + 48;
		n /= 10;
		i--;
	}
	return (res);
}

static int	ft_mallocsize(int n)
{
	int	i;

	i = 1;
	if (n <= 0)
		i++;
	while (n % 10 != 0 || n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static char	*ft_int_min(void)
{
	char	*res;
	int		i;

	i = 12;
	res = malloc(sizeof(char) * i);
	if (!res)
		return (NULL);
	res[0] = '-';
	ft_attrib(-2147483648, res, i - 2);
	res[10] += 1;
	res[11] = '\0';
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		i;

	if (n == -0)
		n = 0;
	if (n == -2147483648)
	{
		res = (char *)ft_int_min();
		return (res);
	}
	i = ft_mallocsize(n);
	res = malloc(sizeof(char) * i);
	if (!res)
		return (NULL);
	if (n < 0)
		res[0] = '-';
	ft_attrib(n, res, i - 2);
	res[i - 1] = '\0';
	return (res);
}
