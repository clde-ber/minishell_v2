#include "minishell.h"

/*
** Functions that help managing environment variables chained list. Output variable name, check whether there are doublons in environement variable
** names in the command line itself or compare new variables names with existing ones. If so, variable values are replaced by the last one that are set.
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
			replace_env(tab[k], var_env);
			k--;
		}
		k = j - 1;
		var_env = var_env->next;
	}
	replace_env(tab[k], var_env);
	return (var_env);
}

void replace_env(char *tab, t_list *var_env)
{
	if (ft_strcmp(ft_get_name(tab), var_env->name) == 0)
	{
		if (ft_strchr(tab, '='))
			var_env->value = ft_strdup(ft_strchr(tab, '=') + 1);
		else
			var_env->value = ft_strdup("");
		tab[0] = '\0';
	}
}

