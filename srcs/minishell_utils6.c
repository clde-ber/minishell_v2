/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/02 14:17:52 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/02 14:26:27 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*free_null(char *str)
{
	free(str);
	str = NULL;
	return (str);
}

int	handle_j_down(t_term *term)
{
	int	j;

	if (term->where == -1)
		j = ft_strlen(term->done[0]);
	else
		j = ft_strlen(term->done[term->where + 1]);
	if (j + 18 > term->col)
		tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 2), 1,
			ft_putchar);
	else
		tputs(tgoto(tgetstr("cm", NULL), term->x - 1, term->y - 1), 1,
			ft_putchar);
	return (j);
}
