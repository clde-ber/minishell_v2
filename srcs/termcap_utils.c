/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   termcap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:28:09 by budal-bi          #+#    #+#             */
/*   Updated: 2021/06/17 15:06:41 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*handle_delete(char *current, t_term *term)
{
	char	*buf;

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
		// buf = ft_strdup(current);
		// free(current);
		// current = ft_strdup(buf);
		// free(buf);
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