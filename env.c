#include "minishell.h"

char *ft_get_name(char *str)
{
    int i;
    int boolean;
    char *copy;

    i = 0;
    boolean = 0;
    copy = ft_strdup(str);
    while (copy[i] && boolean == 0)
    {
        if (copy[i] == '=')
        {
            copy[i] = '\0';
            boolean = 1;
        }
        i++;
    }
    while (copy[i])
    {
        copy[i] = '\0';
        i++;
    }
    return (copy);
}

t_list *set_new_env(char **env, char **tab, t_list *var_env)
{
	int k;
    t_list *tmp;
    t_list *first;

	k = 0;
	while (env[k])
		k++;
	k--;
	var_env = ft_lstnew(ft_get_name(env[k]), ft_strchr(env[k], '=') + 1);
	while (k >= 0)
	{
		ft_lstadd_front(&var_env, ft_lstnew(ft_get_name(env[k]), ft_strchr(env[k], '=') + 1));
		ft_lstiter(var_env, &ft_record, env[k]);
		k--;
	}
	return (var_env);
}

t_list *set_env(char **env, char **tab, t_list *var_env)
{
    int i;
	int j;

	j = 0;
	while (tab[j])
		j++;
    i = j - 1;
	while (var_env->next)
		var_env = var_env->next;
	while (i >= 1)
    {
		ft_lstadd_back(&var_env, ft_lstnew(ft_get_name(tab[i]), ft_strchr(tab[i], '=') + 1));
		ft_lstiter(var_env, &ft_record, tab[i]);
		i--;
	}
	return (var_env);
}

t_list	*unset(t_list *env, char **tab)
{
	int i;
	int j = 0;

	while (tab[j])
		j++;
	i = 1;
	while (env->next)
	{
		while (i < j)
		{
			if (strcmp(tab[i], env->name) == 0)
			{
				env->name = "";
				env->value = "";
			}
			i++;
		}
		env = env->next;
		i = 1;
	}
	return (env);
}

void print_env(char **tab, t_list *environ)
{
	char *str = NULL;
	char *str2 = NULL;
	while (environ->next)
	{
		if (ft_strlen(environ->name))
    	{
			str2 = ft_strjoin(environ->name, "=");
			str = ft_strjoin(str2, environ->value);
			printf("%s\n", str);
		}
		environ = environ->next;
	}
}