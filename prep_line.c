/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/16 16:24:12 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/19 16:52:37 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char *end_line(char *current, t_term *term)
{
	restore_term(term);
	if (current == NULL)
		current = ft_strdup("\0");
	if ((term->len > 0 && ft_strcmp(current, term->done[0]) != 0) || term->len == 0)
		term->done = save_input(current, term->done);
	write(1, "\n", 1);
	// if (term->last != NULL)
	// 	free(term->last);
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
			restore_term(term);
			if (current != NULL)
				free(current);
			write(1, "\n", 1);
			exit(0);
		}
		else
			current = get_char(current, term, buf);
		buf[0] = '\0';
	}
	return (NULL);
}

char *getcommand(char *str)
{
	int i;
	int j;
	char *ret;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != ';')
		i++;
	if (i == 0)
		return (NULL);
	if (i == ft_strlen(str))
		return (str);
	if (!(ret = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}