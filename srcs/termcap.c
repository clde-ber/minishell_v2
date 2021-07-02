/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:13:21 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/02 14:16:49 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**save_input(char *str, char **save)
{
	char	**buf;
	int		j;

	j = 0;
	if (save == NULL)
	{
		save = malloc(sizeof(char *) * 2);
		if (!save)
			return (NULL);
		save[0] = ft_strdup(str);
		save[1] = NULL;
		return (save);
	}
	buf = malloc(sizeof(char *) * (count_tabs(save) + 2));
	if (!buf)
		return (NULL);
	buf[j] = ft_strdup(str);
	while (save[j])
	{
		buf[j + 1] = ft_strdup(save[j]);
		j++;
	}
	buf[j + 1] = NULL;
	free_tabtab(save);
	return (buf);
}

void	restore_term(t_term *term)
{
	tcsetattr(0, TCSANOW, &term->s_termios_backup);
}

void	get_cursor_pos(t_term *term, char **res)
{
	char	*temp;

	if ((int)res[0][0] != 27 || res[0][1] != '[')
	{
		free_tabtab(res);
		return ;
	}
	temp = ft_strdup(&res[0][2]);
	term->y = ft_atoi(temp);
	term->x = ft_atoi(res[1]);
	term->size = ft_strlen(res[0]) + ft_strlen(res[1]);
	free(temp);
	free_tabtab(res);
}

void	get_cursor_space(t_term *term)
{
	char	buf[2];
	char	*check;
	char	*buf1;

	check = NULL;
	write(1, "\033[6n", 4);
	while (buf[0] != 'R')
	{
		read(0, buf, 1);
		buf[1] = '\0';
		if (check == NULL)
			check = ft_strdup(buf);
		else
		{
			buf1 = ft_strdup(buf);
			check = ft_strjoin_free(check, buf1);
		}
	}
	if (ft_strlen(check) < 2)
		return ;
	get_cursor_pos(term, ft_split(check, ";"));
	free(check);
}

void	init_term(t_term *term)
{
	tgetent(NULL, getenv("TERM"));
	term->where = -1;
	term->x = 0;
	term->col = tgetnum("co");
	term->lin = tgetnum("li");
	term->y = 0;
	tcgetattr(0, &term->s_termios);
	term->s_termios_backup = term->s_termios;
	term->s_termios.c_lflag &= ~(ICANON);
	term->s_termios.c_lflag &= ~(ECHO);
	if (tcsetattr(0, TCSANOW, &term->s_termios) == -1)
		return ;
	if (term->done)
		term->len = count_tabs(term->done);
	else
		term->len = 0;
	term->mtline = 0;
	term->last = NULL;
}
