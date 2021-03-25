#include "minishell.h"

t_list ft_record(void *lst, void *str, void *cmd)
{
    ((t_list *)lst)->name = ft_get_name(str);
    ((t_list *)lst)->value = ft_strchr(str, '=') + 1;
	if (strcmp(((char *)((t_list *)lst)->name), "PATH") == 0)
		((t_command *)cmd)->path = ft_strdup(((char *)((t_list *)lst)->value));
}

void	ft_lstiter(t_list *lst, t_list (*f)(void *, void *, void *), char *str, t_command *cmd)
{
    int i = 0;
	if (!lst || !f)
		return ;
	f(lst, str, cmd);
	lst = lst->next;
}