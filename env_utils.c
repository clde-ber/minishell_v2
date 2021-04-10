#include "minishell.h"

/*
** Functions that help managing environment variables linked list. Output variable name, check whether there are doublons in environement variable
** names in the command line itself or compare new variables names with existing ones. If so, variable values are replaced by the last one that are set.
** If += symbols, associated env varibale value is added to existing one.
*/

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
        if (copy[i] == '=' || (copy[i] == '+' && copy[i + 1] == '=') ||
		(copy[i] == '+' && copy[i + 1] == '\0'))
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

void add_to_env(char **tab, int k, int l)
{
	char *i_name;
	char *j_name;
	char *i_value;
	char *j_value;

	i_name = ft_get_name(tab[k]);
	j_name = ft_get_name(tab[l]);
	if (ft_strchr(tab[k], '='))
		i_value = ft_strdup(ft_strchr(tab[k], '='));
	else
		i_value = ft_strdup("");
	if (ft_strchr(tab[l], '='))
		j_value = ft_strdup(ft_strchr(tab[l], '='));
	else
		j_value = ft_strdup("");
	if (l > k)
	{
		if (ft_strchr(tab[l], '+') && ft_strchr(tab[k], '=') &&
		ft_strchr(tab[l], '='))
		{
			free(tab[l]);
			tab[l] = join_a_free(join_a_free(join_a_free(j_name, "\
+="), &i_value[1]), &j_value[1]);
			free(i_name);
		}
		else
		{
			free(i_name);
			free(j_name);
		}
	}
	else if (l < k)
	{
		if (ft_strchr(tab[k], '+') && ft_strchr(tab[k], '=') &&
		ft_strchr(tab[l], '='))
		{
			free(tab[k]);
			tab[k] = join_a_free(join_a_free(join_a_free(i_name, "\
+="), &j_value[1]), &i_value[1]);
			free(j_name);
		}
		else
		{
			free(i_name);
			free(j_name);
		}
	}
	else
	{
		free(i_name);
		free(j_name);
	}
	free(i_value);
	free(j_value);
}

void check_doublons_cl(char **tab)
{
	int k;
	int l;
	int j;
	char *i_name;
	char *j_name;

	j = 0;
	i_name = NULL;
	j_name = NULL;
	while (tab[j])
		j++;
	k = j - 1;
	l = j - 1;
	while (k >= 1)
	{
		while (l >= 1)
		{
			i_name = ft_get_name(tab[k]);
			j_name = ft_get_name(tab[l]);
			if (ft_strcmp(i_name, j_name) == 0)
			{
				add_to_env(tab, k, l);
				if (l > k)
					tab[k][0] = '\0';
				else if (l < k)
					tab[l][0] = '\0';
			}
			l--;
			free(i_name);
			free(j_name);
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
		while (k > 0)
		{
			replace_env(tab[k], var_env);
			k--;
		}
		k = j - 1;
		var_env = var_env->next;
	}
	k = j - 1;
	while (k > 0)
	{
		replace_env(tab[k], var_env);
		k--;
	}
	return (var_env);
}

void replace_env(char *tab, t_list *var_env)
{
	char *name;

	name = ft_get_name(tab);
	if (ft_strcmp(name, var_env->name) == 0)
	{
		if (ft_strchr(tab, '+') && ft_strchr(tab, '='))
			var_env->value = ft_strjoin(var_env->value,
			&ft_strchr(tab, '=')[1]);
		else if (ft_strchr(tab, '='))
			var_env->value = ft_strdup(&ft_strchr(tab, '=')[1]);
		else
			((char *)var_env->value)[0] = '\0';
		tab[0] = '\0';
	}
	free(name);
}