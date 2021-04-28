#include "minishell.h"

void	ft_record(void *lst, void *cmd)
{
	if (strcmp(((char *)((t_list *)lst)->name), "PATH") == 0)
	{
		if (((t_command *)cmd)->path)
		{
			free(((t_command *)cmd)->path);
			((t_command *)cmd)->path = NULL;
		}
		((t_command *)cmd)->path = ft_strdup(((char *)((t_list *)lst)->value));
	}
}

void	ft_lstiter(t_list *lst, void (*f)(void *, void *), t_command *cmd)
{
	if (!lst || !f)
		return ;
	f(lst, cmd);
	lst = lst->next;
}

void	ft_lstdel(t_list *lst)
{
	t_list	*buf;

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
