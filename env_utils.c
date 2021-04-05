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
        if (copy[i] == '=' || copy[i] == '+')
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
	if (l > k)
	{
		if (ft_strchr(tab[l], '+') && ft_strchr(tab[k], '=') &&
		ft_strchr(tab[l], '='))
			tab[l] = ft_strjoin(ft_strjoin(ft_strjoin(ft_get_name(tab[l]), "\
+="), ft_strchr(tab[k], '=') + 1), ft_strchr(tab[l], '=') + 1);
	}
	else if (l < k)
	{
		if (ft_strchr(tab[k], '+') && ft_strchr(tab[k], '=') &&
		ft_strchr(tab[l], '='))
			tab[k] = ft_strjoin(ft_strjoin(ft_strjoin(ft_get_name(tab[k]), "\
+="), ft_strchr(tab[l], '=') + 1), ft_strchr(tab[k], '=') + 1);
	}
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
			if (ft_strcmp(ft_get_name(tab[k]), ft_get_name(tab[l])) == 0)
			{
				add_to_env(tab, k, l);
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
	k = 0;
	while (tab[k])
	{
		printf("tab[k]%s\n", tab[k]);
		k++;
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
	if (ft_strcmp(ft_get_name(tab), var_env->name) == 0)
	{
		if (ft_strchr(tab, '+') && ft_strchr(tab, '='))
			var_env->value = ft_strjoin(var_env->value,
			ft_strchr(tab, '=') + 1);
		else if (ft_strchr(tab, '='))
			var_env->value = ft_strdup(ft_strchr(tab, '=') + 1);
		else
			var_env->value = ft_strdup("");
		tab[0] = '\0';
	}
}