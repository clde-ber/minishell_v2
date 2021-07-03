/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:16:23 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/03 13:53:55 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_j_up(t_term *term)
{
	int	j;

	if (term->where == 0)
	{
		if (term->last != NULL)
			j = ft_strlen(term->last);
		else
			j = 0;
	}
	else
	{
		j = ft_strlen(term->done[term->where - 1]);
		if (j + 18 > term->col)
			tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 2), 1,
				ft_putchar);
		else
			tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 1), 1,
				ft_putchar);
	}
	return (j);
}

char	*handle_arrow_up(t_term *term, char *end)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = term->x - 1;
	if (term->where == term->len - 1)
		return (end);
	if (term->where != -1 && end != NULL && ft_strcmp(end,
			term->done[term->where]) != 0)
		term->done = replace_tabtab(term->done, term->where, end);
	term->where++;
	j = handle_j_up(term);
	while (i <= j)
	{
		write(1, " ", 1);
		i++;
	}
	get_cursor_space(term);
	term->x = k + 1;
	tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 1), 1, ft_putchar);
	ft_putstr_fd(term->done[term->where], 1);
	if (end != NULL)
		free(end);
	return (ft_strdup(term->done[term->where]));
}

char	*handle_end_up(t_term *term, char *end, int k)
{
	get_cursor_space(term);
	term->x = k;
	tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 1), 1, ft_putchar);
	if (term->where == -1 && term->mtline == 0)
	{
		free(end);
		return (NULL);
	}
	else if (term->where == -1 && end != NULL)
		end = handle_hist(term, end);
	else
	{
		ft_putstr_fd(term->done[term->where], 1);
		free(end);
		end = ft_strdup(term->done[term->where]);
	}
	return (end);
}

char	*handle_arrow_down(t_term *term, char *end)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	k = term->x;
	if (term->where == -1)
		return (end);
	if (term->where != -1 && end != NULL && ft_strcmp(end,
			term->done[term->where]) != 0)
		term->done = replace_tabtab(term->done, term->where, end);
	term->where--;
	j = handle_j_down(term);
	while (i <= j)
	{
		write(1, " ", 1);
		i++;
	}
	return (end = handle_end_up(term, end, k));
}

char	*handle_arrow(t_term *term, char *current)
{
	char	buf[2];

	read(0, buf, 1);
	if ((int)buf[0] == 91)
	{
		read(0, buf, 1);
		if ((int)buf[0] != 66 && (int)buf[0] != 65)
			return (current);
		if (term->len == 0)
			return (current);
		if (current != NULL && term->where == -1)
		{
			if (term->last != NULL)
				free(term->last);
			term->last = ft_strdup(current);
		}
		if ((int)buf[0] == 65)
			current = handle_arrow_up(term, current);
		else if ((int)buf[0] == 66)
			current = handle_arrow_down(term, current);
	}
	return (current);
}
