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

void check_doublons_cl(char **env, char **tab, t_list *var_env, t_command *cmd)
{
	int k;
	int l;
	int j;

	j = 0;
	while (tab[j])
		j++;
	k = j - 1;
	l = j - 1;
	while (k >= 1)
	{
		while (l >= 1)
		{
			if (strcmp(ft_get_name(tab[k]), ft_get_name(tab[l])) == 0)
			{
				if (l > k)
					tab[k] = ft_strdup("");
				else if (l < k)
					tab[l] = ft_strdup("");
			}
			l--;
		}
		l = j - 1;
		k--;
	}
}

t_list *check_doublons(int k, int j, char **tab, t_list *var_env)
{
	k = j - 1;
	while (var_env->next)
	{
		while (k >= 1)
		{
			if (strcmp(ft_get_name(tab[k]), var_env->name) == 0)
			{
				if (ft_strchr(tab[k], '='))
					var_env->value = ft_strdup(ft_strchr(tab[k], '=') + 1);
				else
					var_env->value = ft_strdup("");
				tab[k][0] = '=';
				tab[k][1] = '\0';
			}
			k--;
		}
		k = j - 1;
		var_env = var_env->next;
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