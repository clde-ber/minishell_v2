#include "minishell.h"

t_list ft_record(void *lst, void *str)
{
    ((t_list *)lst)->name = ft_get_name(str);
    ((t_list *)lst)->value = ft_strchr(str, '=') + 1;
}

void	ft_lstiter(t_list *lst, t_list (*f)(void *, void *), char *str)
{
    int i = 0;
	if (!lst || !f)
		return ;
	f(lst, str);
	lst = lst->next;
}