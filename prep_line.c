/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:24:12 by budal-bi          #+#    #+#             */
/*   Updated: 2021/06/16 11:59:24 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *end_line(char *current, t_term *term)
{
	restore_term(term);
	if (current == NULL)
	{
		write(1, "\n", 1);
		return (current);
	}
	if ((term->len > 0 && ft_strcmp(current, term->done[0]) != 0) || term->len == 0)
		term->done = save_input(current, term->done);
	write(1, "\n", 1);
	return (current);
}

char *get_char(char *current, t_term *term, char *buf)
{
	char *buf1;

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

char	*handle_delete(char *current, t_term *term)
{
	if (current == NULL || ft_strlen(current) == 0)
		;
	else
	{
		tputs(tgoto(tgetstr("cm", NULL), (term->x + ft_strlen(current) - 2),
		term->y - 1), 1, ft_putchar);
		write(1, " ", 1);
		tputs(tgoto(tgetstr("cm", NULL), (term->x + ft_strlen(current) - 2),
		term->y - 1), 1, ft_putchar);
		current[ft_strlen(current) - 1] = '\0';
	}
	return (current);
}

void	handle_ctrl_d(char *current, t_term *term)
{
	restore_term(term);
	if (current != NULL)
		free(current);
	write(1, "\n", 1);
}

char *go_line(t_term *term)
{
	char buf[2];
	char *current;

	init_term(term);
	current = NULL;
	get_cursor_space(term);
	while (read(0, buf, 1) != -1)
	{
		buf[1] = '\0';
		if (buf[0] == '\n' || (int)buf[0] == 13)
			return (end_line(current, term));
		else if ((int)buf[0] == 27)
			current = handle_arrow(term, current);
		else if ((int)buf[0] == 4)
		{
			handle_ctrl_d(current, term);
			exit(0);
		}
		else if((int)buf[0] == 127)
			current = handle_delete(current, term);
		else
			current = get_char(current, term, buf);
		buf[0] = '\0';
	}
	return (NULL);
}

char	*getcommand(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && ((str[i] != ';' || (str[i] == ';' && \
	(i && str[i - 1] == '\\'))) || is_in_string(str, i)))
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!(ret))
		return (NULL);
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}
