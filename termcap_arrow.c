/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:16:23 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/31 16:55:53 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_arrow_up(t_term *term, char *end)
{
	int i = 0;
	int j;
	int k;

	i = 0;
	k = term->x - 1;
	if (term->where == term->len - 1)
		return (end);
	if (term->where != -1 && end != NULL && ft_strcmp(end,
	term->done[term->where]) != 0)
		term->done = replace_tabtab(term->done, term->where, end);
	term->where++;
	if (term->where == 0)
		j = ft_strlen(term->last);
	else
		j = ft_strlen(term->done[term->where - 1]);
	if (j + 18 > term->col)
		tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 2), 1, ft_putchar);
	else
		tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 1), 1, ft_putchar);
	while (i <= j)
	{
		write(1, " ", 1);
		i++;
	}
	get_cursor_space(term);
	term->x = k + 1;
		tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y), 1, ft_putchar);
	ft_putstr_fd(term->done[term->where], 1);
	if (end != NULL)
		free(end);
	end = ft_strdup(term->done[term->where]);
	return (end);
}

char	*handle_arrow_down(t_term *term, char *end)
{
	int i;
	int j;
	int k;

	i = 0;
	k = term->x;
	if (term->where == -1)
		return (end);
	if (term->where != -1 && end != NULL && ft_strcmp(end,
	term->done[term->where]) != 0)
		term->done = replace_tabtab(term->done, term->where, end);
	term->where--;
	if (term->where == -1)
		j = ft_strlen(term->done[0]);
	else
		j = ft_strlen(term->done[term->where + 1]);
	if (j + 18 > term->col)
		tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 2), 1, ft_putchar);
	else
		tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 1), 1, ft_putchar);
	while (i <= j)
	{
		write(1, " ", 1);
		i++;
	}
	get_cursor_space(term);
	term->x = k;
	tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y), 1, ft_putchar);
	if (term->where == -1 && term->mtline == 0)
	{
		free(end);
		return (NULL);
	}
	else if (term->where == -1 && end != NULL)
	{
		ft_putstr_fd(term->last, 1);
		if (end != NULL)
			free(end);
		end = ft_strdup(term->last);
	}
	else
	{
		ft_putstr_fd(term->done[term->where], 1);
		free(end);
		end = ft_strdup(term->done[term->where]);
	}
	return (end);
}

char	*handle_arrow(t_term *term, char *current)
{
	char	buf[2];

	read(0, buf, 1);
	if ((int)buf[0] == 91)
	{
		read(0, buf, 1);
		if (term->len == 0)
			return (current);
		if (current != NULL && term->where == -1)
			term->last = ft_strdup(current);
		if ((int)buf[0] == 65)
			current = handle_arrow_up(term, current);
		else if ((int)buf[0] == 66)
			current = handle_arrow_down(term, current);
	}
	return (current);
}
