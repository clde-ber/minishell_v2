/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 15:55:17 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/10 15:52:04 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_symbol(char c, char comp)
{
	(void)comp;
	if (c == '<' || c == '>' || c == '|' || c == ';')
		return (1);
	return (0);
}

int	count_pipes(char **res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (res[i])
	{
		if (ft_strcmp(res[i], "|") == 0)
			j++;
		i++;
	}
	return (j);
}

int	chrtabtab(char **res, char *str)
{
	int		i;

	i = 0;
	if (!res)
		return (-1);
	while (res[i])
	{
		if (ft_strcmp(res[i], str) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	**replace_tabtab(char **tabl, int i, char *str)
{
	char	**buf;
	int		j;

	j = 0;
	buf = malloc(sizeof(char *) * (count_tabs(tabl) + 1));
	if (!(buf))
		return (NULL);
	while (tabl[j] && j < i)
	{
		buf[j] = ft_strdup(tabl[j]);
		j++;
	}
	buf[j] = ft_strdup(str);
	j++;
	while (tabl[j])
	{
		buf[j] = ft_strdup(tabl[j]);
		j++;
	}
	buf[j] = NULL;
	free_tabtab(tabl);
	return (buf);
}

void	erase_line(int i, int j, t_term *term)
{
	int		k;

	k = 0;
	while (k < (j - i))
	{
		write(1, " ", 1);
		k++;
	}
	tputs(tgoto(tgetstr("cm", NULL), (term->x - 1) + i, term->y - 1), 1,
		ft_putchar);
}
