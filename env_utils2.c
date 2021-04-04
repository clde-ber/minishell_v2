/*
** Functions that output a two dimensional array for environment values, sort it and print it.
*/

#include "minishell.h"

char **fill_list(t_list *environ, char **list, int i)
{
	while (environ->next)
		environ = environ->next;
	while (environ->prec)
	{
		environ = environ->prec;
		i++;
	}
	if (!(list = malloc(sizeof(char *) * (i + 2))))
		return (0);
	i = 0;
	while (environ)
	{
		if (ft_strlen(environ->name))
    	{
			list[i] = ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin(ft_strjoin("de\
clare -x ", environ->name), "="), "\""), environ->value), "\"");
			i++;
		}
		environ = environ->next;
	}
	list[i] = NULL;
	return (list);
}

char **sort_list(t_list *environ, char **list, int i, int j)
{
	char *tmp;

	tmp = NULL;
	while (list[i])
	{
		while (list[j])
		{
			if (strcmp(ft_get_name(list[i]), ft_get_name(list[j])) < 0)
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (list);
}

void print_sorted_env(t_list *environ)
{
	char **list;
	int i;
	int j;

	list = NULL;
	i = 0;
	j = 0;
	list = fill_list(environ, list, i);
	list = sort_list(environ, list, i, j);
	while (list[i])
	{
		printf("%s\n", list[i]);
		i++;
	}
}