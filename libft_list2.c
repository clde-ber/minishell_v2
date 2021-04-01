#include "minishell.h"

t_list ft_record(void *lst, void *str, void *cmd)
{
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

void ft_lstdel(t_list *lst)
{
	t_list *buf;
	
	while (lst)
	{
		buf = lst;
		lst = lst->next;
		free(buf->name);
		buf->name = 0;
		free(buf->value);
		buf->value = 0;
		free(buf);
		buf = 0;
	}
}