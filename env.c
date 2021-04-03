/*
** Functions that manage environment variables chained list - create, amend it & print it. Once the main variable list with environment variables
** imported from computer is created, it is amended with new entries if export is invoked, updated when unset is called, and printed when env is.
*/

#include "minishell.h"

t_list *set_new_env(char **env, char **tab, t_list *var_env, t_command *cmd)
{
	int k;
    char *name;
	char *value;
	t_list *tmp;

	k = 0;
	name = NULL;
	value = NULL;
	tmp = NULL;
	while (env[k])
		k++;
	k--;
	var_env = ft_lstnew((name = ft_get_name(env[k])), (value = ft_strdup(ft_strchr(env[k], '=') + 1)));
	k--;
	while (k >= 0)
	{
		tmp = var_env;
		ft_lstadd_front(&var_env, ft_lstnew((name = ft_get_name(env[k])), (value = ft_strdup(ft_strchr(env[k], '=') + 1))));
		ft_lstiter(var_env, &ft_record, env[k], cmd);
		tmp->prec = var_env;
		k--;
	}
	return (var_env);
}

void set_env(char **env, char **tab, t_list *var_env, t_command *cmd)
{
    int i;
	int j;
	int k;
	t_list *tmp_new;
	t_list *tmp;

	j = 0;
	tmp_new = NULL;
	tmp = NULL;
	while (tab[j])
		j++;
    i = 1;
	tmp = check_doublons(k, j, tab, var_env);
	while (i <= j - 1)
    {
		if (ft_strchr(tab[i], '='))
			ft_lstadd_back(&var_env, (tmp_new = ft_lstnew(ft_get_name(tab[i]), ft_strdup(ft_strchr(tab[i], '=') + 1))));
		else
			ft_lstadd_back(&var_env, (tmp_new = ft_lstnew(ft_get_name(tab[i]), ft_strdup(""))));
		ft_lstiter(var_env, &ft_record, tab[i], cmd);
		tmp->prec = tmp;
		tmp_new = tmp;
		i++;
	}
	var_env = tmp_new;
}

void	unset(t_list *env, char **tab)
{
	int i;
	int j = 0;

	while (tab[j])
		j++;
	i = 1;
	while (env)
	{
		while (i < j)
		{
			if (strcmp(ft_get_name(tab[i]), env->name) == 0)
			{
				env->name = ft_strdup("");
				env->value = ft_strdup("");
			}
			i++;
		}
		env = env->next;
		i = 1;
	}
}

void print_env(t_list *environ)
{
	char *name;
	char *value;

	name = NULL;
	value = NULL;
	while (environ)
	{
		if (ft_strlen(environ->name))
    	{
			name = ft_strjoin(environ->name, "=");
			value = ft_strjoin(name, environ->value);
			printf("%s\n", value);
			free(value);
			free(name);
		}
		environ = environ->next;
	}
}