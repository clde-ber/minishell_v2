/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:56:41 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_lstdelone(t_list *lst)
{
	if (lst)
	{
		lst->name = "\0";
		lst->value = "\0";
	}
}

t_list	*ft_lstnew(char *name, void *value)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!(new))
		return (NULL);
	new->name = name;
	new->value = value;
	new->next = NULL;
	new->prec = NULL;
	return (new);
}

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (alst && new)
	{
		new->next = *alst;
		*alst = new;
	}
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (!new)
		return ;
	if (*alst == NULL)
	{
		*alst = new;
		new->prec = NULL;
	}
	else
	{
		last = ft_lstlast(*alst);
		last->next = new;
		new->next = NULL;
	}
}
