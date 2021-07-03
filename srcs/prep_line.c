/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:24:12 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/03 12:19:32 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*handle_ctrlc(char *current)
{
	if (g_sig.stop == 1 && current == NULL)
		g_sig.stop = 0;
	if (g_sig.stop == 1 && current != NULL)
	{
		g_sig.stop = 0;
		free(current);
		current = NULL;
	}
	return (current);
}

char	*end_line(char *current, t_term *term)
{
	restore_term(term);
	if (g_sig.stop == 1)
		current = handle_ctrlc(current);
	if (current == NULL)
	{
		write(1, "\n", 1);
		return (current);
	}
	if ((term->len > 0 && ft_strcmp(current, term->done[0]) != 0) || \
		term->len == 0)
		term->done = save_input(current, term->done);
	write(1, "\n", 1);
	if (term->last != NULL)
		free(term->last);
	return (current);
}

char	*get_char(char *current, t_term *term, char *buf)
{
	char	*buf1;

	if (term->where == -1)
		term->mtline = 1;
	write(1, &buf[0], 1);
	if (current == NULL)
		current = ft_strdup(buf);
	else
	{
		buf1 = ft_strdup(current);
		free(current);
		current = ft_strjoin(buf1, buf);
		free(buf1);
	}
	return (current);
}

char	*special_line(char *current, char *buf, t_term *term)
{
	if ((int)buf[0] == 12)
	{
		tputs(tgoto(tgetstr("cl", NULL), 0, 0), 1, ft_putchar);
		ft_putstr_fd("***minishell*** > ", 1);
		if (current)
			ft_putstr_fd(current, 1);
	}
	if ((int)buf[0] == 4)
	{
		if (current == NULL)
		{
			handle_ctrl_d(current, term);
			exit(0);
		}
	}
	else if ((int)buf[0] == 127)
		current = handle_delete(current, term);
	else
		current = get_char(current, term, buf);
	return (current);
}

char	*go_line(t_term *term)
{
	char	buf[2];
	char	*current;
	int		res;

	init_term(term);
	g_sig.stop = 0;
	current = NULL;
	get_cursor_space(term);
	res = read(0, buf, 1);
	if (res == -1)
		return (NULL);
	while (buf[0] != '\n')
	{
		if (g_sig.stop == 1)
			current = handle_ctrlc(current);
		buf[1] = '\0';
		if ((int)buf[0] == 27)
			current = handle_arrow(term, current);
		else
			current = special_line(current, buf, term);
		res = read(0, buf, 1);
		if (res == -1)
			return (NULL);
	}
	return (end_line(current, term));
}
