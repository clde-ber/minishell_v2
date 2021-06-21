/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:28:09 by budal-bi          #+#    #+#             */
/*   Updated: 2021/06/21 10:53:21 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
