/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:16:23 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/22 17:08:53 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_arrow_up(t_term *term, char *end)
{
	if (term->where == term->len - 1)
		return (end);
	tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 1), 1, ft_putchar);
	if (term->where != -1 && end != NULL && ft_strcmp(end,
	term->done[term->where]) != 0)
		term->done = replace_tabtab(term->done, term->where, end);
	term->where++;
	ft_putstr_fd(term->done[term->where], 1);
	if (term->where == 0)
		erase_line(ft_strlen(term->done[term->where]), ft_strlen(term->last),
		term);
	else
		erase_line(ft_strlen(term->done[term->where]),
		ft_strlen(term->done[term->where - 1]), term);
	if (end != NULL)
		free(end);
	end = ft_strdup(term->done[term->where]);
	return (end);
}

char	*handle_arrow_down_bis(t_term *term, char *end, int i)
{
	if (i == 0)
	{
		ft_putstr_fd(term->last, 1);
		erase_line(ft_strlen(term->last), ft_strlen(term->done[0]), term);
		if (end != NULL)
			free(end);
		end = ft_strdup(term->last);
	}
	else
	{
		ft_putstr_fd(term->done[term->where], 1);
		if (term->where != term->len)
			erase_line(ft_strlen(term->done[term->where]),
	ft_strlen(term->done[term->where + 1]), term);
		free(end);
		end = ft_strdup(term->done[term->where]);
	}
	return (end);
}

char	*handle_arrow_down(t_term *term, char *end)
{
	if (term->where == -1)
		return (end);
	tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 1), 1, ft_putchar);
	if (term->where != -1 && end != NULL && ft_strcmp(end,
	term->done[term->where]) != 0)
		term->done = replace_tabtab(term->done, term->where, end);
	term->where--;
	if (term->where == -1 && term->mtline == 0)
	{
		erase_line(0, ft_strlen(term->done[0]), term);
		free(end);
		return (NULL);
	}
	else if (term->where == -1 && end != NULL)
		end = handle_arrow_down_bis(term, end, 0);
	else
		end = handle_arrow_down_bis(term, end, 1);
	return (end);
}

void	not_arrow(int i, char c, t_term *term)
{
	if (i == 0)
	{
		ft_putchar(27);
		write(1, &c, 1);
	}
	else
	{
		ft_putchar(27);
		ft_putchar(91);
		write(1, &c, 1);
	}
}

char	*handle_arrow(t_term *term, char *current)
{
	char	buf[2];

	read(0, buf, 1);
	if ((int)buf[0] == 91)
	{
		read(0, buf, 1);
		if ((int)buf[0] != 66 && (int)buf[0] != 65)
			not_arrow(1, buf[0], term);
		else
		{
			if (term->len == 0)
				return (current);
			if (current != NULL && term->where == -1)
				term->last = ft_strdup(current);
			if ((int)buf[0] == 65)
				current = handle_arrow_up(term, current);
			else if ((int)buf[0] == 66)
				current = handle_arrow_down(term, current);
		}
	}
	else
		not_arrow(0, buf[0], term);
	return (current);
}
