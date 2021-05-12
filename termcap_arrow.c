/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_arrow.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/02 19:16:23 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/06 17:10:01 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char **replace_tabtab(char **tabl, int i, char *str)
{
    char **buf;
    int j;

    j = 0;
    if (!(buf = sizeof(char *) * (count_tabs(tabl) + 1)))
        return (NULL);
    while (j < i && tabl[j])
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
	int k;

	k = 0;
	while (k < (j - i))
	{
		write(1, " ", 1);
		k++;
	}
	tputs(tgoto(tgetstr("cm", NULL), (term->x - 1) + i, term->y), 1, ft_putchar);
}

char *handle_arrow_up(t_term *term, t_save *save, char *end)
{
	if (save->where == save->size - 1)
        return (end);
    tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y), 1, ft_putchar);
	if (save->where != -1 && end != NULL && ft_strcmp(end, save->done[save->where]) != 0)
        save->done = replace_tabtab(save->done, save->where, end);
    save->where++;
    ft_putstr_fd(save->done[save->where], 1);
    if (save->where == 0)
        erase_line(ft_strlen(save->done[save->where]), ft_strlen(save->last), term);
    else
		erase_line(ft_strlen(save->done[save->where]), ft_strlen(save->done[save->where - 1]), term);
	if (end != NULL)
        free(end);
	end = ft_strdup(save->done[save->where]);;
	return (end);
}

char *handle_arrow_down(t_term *term, t_save *save, char *end)
{
	if (save->where == -1)
        return (end);
    tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y), 1, ft_putchar);
    if (save->where != -1 && end != NULL && ft_strcmp(end, save->done[save->where]) != 0)
        save->done = replace_tabtab(save->done, save->where, end);
    save->where--;
    if (save->where == -1 && save->mtline == 0)
    {
        erase_line(0, ft_strlen(save->done[0]), term);
        return (NULL);
    }
    else if (save->where == -1 && end != NULL)
    {
        ft_putstr_fd(save->last, 1);
        erase_line(ft_strlen(save->last), ft_strlen(save->done[0]), term);
        if (end != NULL)
            free(end);
	    end = ft_strdup(save->last);
    }
    else
    {
        ft_putstr_fd(save->done[save->where], 1);
        if (save->where != save->size)
            erase_line(ft_strlen(save->done[save->where]), ft_strlen(save->done[save->where + 1]), term);
        free(end);
        end = ft_strdup(save->done[save->where]);
    }
	return (end);
}

void not_arrow(int i, char c, t_term *term)
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

//get cursor space and set it after prompt before writing line, then at end of line
// Clean up the rowscols (from \033[rows;cols -- the R at end was eaten)
// rowscols="${rowscols//[^0-9;]/}"
// rowscols=("${rowscols//;/ }")

//if save dispay avec arrow et apres entrée, que faire?

char *handle_arrow(t_term *term, t_save *save, char *current)
{
	char buf[2];
	
	read(0, buf, 1);
	if ((int)buf[0] == 91)
	{
		read(0, buf, 1);
        if ((int)buf[0] != 66 && (int)buf[0] != 65)
			not_arrow(1, buf[0], term);
        else
        {
            if (save->size == 0)
                return (current);
            if (current != NULL && save->where == -1)
                save->last = ft_strdup(current);
            if ((int)buf[0] == 65)
                current = handle_arrow_up(term, save, current);
            else if ((int)buf[0] == 66)
                current = handle_arrow_down(term, save, current);
        }
	}
	else
		not_arrow(0, buf[0], term);
	return (current);
}
