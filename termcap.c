/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 15:13:21 by budal-bi          #+#    #+#             */
/*   Updated: 2021/04/28 15:14:40 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char  **save_input(char *str, char **save)
{
	int i;
	char **buf;
	int j;

	j = 0;
	if (save == NULL)
	{
		i = 0;
		if (!(save = malloc(sizeof(char *) * 2)))
			return (NULL);
		save[i] = ft_strdup(str);
		save[i + 1] = NULL;
		return (save);
	}
	i = count_tabs(save);
	if (!(buf = malloc(sizeof(char *) * (i + 2))))
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
	term->s_termios.c_lflag = term->s_termios_backup.c_lflag;
	term->s_termios.c_lflag = term->s_termios_backup.c_lflag;
	tcsetattr(STDOUT_FILENO, TCSANOW, &term->s_termios);
}

void	get_cursor_pos(t_term *term, char **res)
{
	char *temp;
	int i;
	
	i = 0;
	if ((int)res[0][0] != 27 || res[0][1] != '[')
		return;
	temp = ft_strdup(&res[0][2]);
	term->y = ft_atoi(temp);
	term->x = ft_atoi(res[1]);
	term->size = ft_strlen(res[0]) + ft_strlen(res[1]);
	free(temp);
	free_tabtab(res);
	// tputs(tgoto(tgetstr("cm", NULL), (term->x - term->size) + 6, term->y), 1, ft_putchar);
	// while (i < (term->x - term->size) + 6)
	// {
	// 	write(1, " ", 1);
	// 	i++;
	// }
}

void get_cursor_space(t_term *term)
{
	int i;
	char buf[2];
	char *check;
	char *buf1;

	i = 0;
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
		return;
	get_cursor_pos(term, ft_split(check, ";"));
}

void	init_term(t_term *term)
{
	tgetent(NULL, getenv("TERM"));
	tcgetattr(STDOUT_FILENO, &term->s_termios);
	tcgetattr(STDOUT_FILENO, &term->s_termios_backup);
	term->col = tgetnum("co");
	term->li = tgetnum("li");
	term->x = 0;
	term->y = 0;
}