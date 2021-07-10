/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 16:41:01 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/10 15:52:18 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_test	*ft_lstlast2(t_test *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_test	*get_prec(t_test *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back2(t_test **start, t_test *new)
{
	t_test	*last;

	if (!new)
		return ;
	if (*start == NULL)
	{
		*start = new;
		new->prec = NULL;
	}
	else
	{
		last = ft_lstlast2(*start);
		last->next = new;
		new->prec = last;
		new->next = NULL;
	}
}

t_test	*ft_lstnew2(char **res)
{
	t_test	*new;

	new = malloc(sizeof(t_test));
	if (!(new))
		return (NULL);
	new->res = res;
	new->next = NULL;
	new->prec = NULL;
	return (new);
}

void	destroy_list(t_test **start, t_test *t)
{
	t_test	*buf;
	t_test	*buf1;

	while (t->prec != NULL)
		t = t->prec;
	start = &t;
	buf1 = *start;
	while (buf1)
	{
		buf = buf1->next;
		free(buf1);
		buf1 = buf;
	}
	*start = NULL;
}
