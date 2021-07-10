/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils5.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/23 12:48:39 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/08 16:12:48 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	conv_char_int(char str, int k)
{
	k *= 10;
	k += str - 48;
	return (k);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			j;
	int			k;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r' || \
		str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			j++;
		i++;
	}
	while (str[i] <= '9' && str[i] >= '0')
	{
		k = conv_char_int(str[i], k);
		i++;
	}
	if (j % 2 != 0)
		return (k * -1);
	return (k);
}

static int	len_int(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (11);
	else if (n <= 2147483647 && n > -2147483648)
	{
		if (n == 0)
			return (1);
		if (n < 0)
		{
			n = -n;
			i += 1;
		}
		while (n > 0)
		{
			n = n / 10;
			i++;
		}
	}
	return (i);
}

static int	ft_pow(int nb, int pow)
{
	int	i;
	int	res;

	i = 0;
	res = 1;
	while (i < pow)
	{
		res = res * nb;
		i++;
	}
	return (res);
}

char	*rv_itoa(int n, char *buf)
{
	int		i;
	int		j;
	int		k;
	char	*str;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	i = -1;
	k = n;
	j = len_int(k);
	str = malloc(sizeof(char) * (len_int(n) + 1));
	if (!(str))
		return (0);
	if ((int)n < 0 && k != -2147483648)
		n = -n;
	while (j-- > 0 && k != -2147483648)
		if (i++ <= len_int(k))
			str[j] = ((n / ft_pow(10, i)) % 10) + '0';
	str[len_int(k)] = '\0';
	if (k < 0 && k != -2147483648)
		str[0] = '-';
	free_string(buf);
	return (str);
}
