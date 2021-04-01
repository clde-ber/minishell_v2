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
    char *str;
	char *str2;
	t_list *tmp;

	k = 0;
	str = NULL;
	str2 = NULL;
	tmp = NULL;
	while (env[k])
		k++;
	k--;
	var_env = ft_lstnew((str = ft_get_name(env[k])), (str2 = ft_strdup(ft_strchr(env[k], '=') + 1)));
	while (k >= 0)
	{
		tmp = var_env;
		ft_lstadd_front(&var_env, ft_lstnew((str = ft_get_name(env[k])), (str2 = ft_strdup(ft_strchr(env[k], '=') + 1))));
		ft_lstiter(var_env, &ft_record, env[k], cmd);
		tmp->prec = var_env;
		k--;
	}
	return (var_env);
}

void check_doublons(char **env, char **tab, t_list *var_env, t_command *cmd)
{
	int k;
	int l;
	int j;
	char *str;
	char *str2;

	j = 0;
	while (tab[j])
		j++;
	k = j - 1;
	l = j - 1;
	while (k >= 1)
	{
		while (l >= 1)
		{
			if (strcmp((str = ft_get_name(tab[k])), (str2 = ft_get_name(tab[l]))) == 0)
			{
				if (l > k)
				{
					tab[k][0] = '=';
					tab[k][1] =  '\0';
				}
				else if (l < k)
				{
					tab[l][0] = '=';
					tab[l][1] = '\0';
				}
			}
			free(str);
			free(str2);
			l--;
		}
		l = j - 1;
		k--;
	}
}

void set_env(char **env, char **tab, t_list *var_env, t_command *cmd)
{
    int i;
	int j;
	int k;
	char *str;
	char *str2;
	t_list *tmp;
	t_list *tmp2;

	j = 0;
	str = NULL;
	tmp = NULL;
	tmp2 = NULL;
	while (tab[j])
		j++;
    i = 1;
	k = j - 1;
	while (var_env->next)
	{
		while (k >= 1)
		{
			if (strcmp((str = ft_get_name(tab[k])), var_env->name) == 0)
			{
				if (ft_strchr(tab[k], '='))
					var_env->value = ft_strdup(ft_strchr(tab[k], '=') + 1);
				else
					var_env->value = ft_strdup("");
				tab[k][0] = '=';
				tab[k][1] = '\0';
			}
			k--;
			free(str);
		}
		k = j - 1;
		var_env = var_env->next;
	}
	tmp2 = var_env;
	while (i <= j - 1)
    {
		if (ft_strchr(tab[i], '='))
			ft_lstadd_back(&var_env, (tmp = ft_lstnew((str = ft_get_name(tab[i])), (str2 = ft_strdup(ft_strchr(tab[i], '=') + 1)))));
		else
			ft_lstadd_back(&var_env, (tmp = ft_lstnew((str = ft_get_name(tab[i])), (str2 = ft_strdup("")))));
		ft_lstiter(var_env, &ft_record, tab[i], cmd);
		tmp->prec = tmp2;
		tmp2 = tmp;
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

// a pas besoin de tab? a enlever?
void print_env(char **tab, t_list *environ)
{
	char *str = NULL;
	char *str2 = NULL;
	while (environ)
	{
		if (ft_strlen(environ->name))
    	{
			str2 = ft_strjoin(environ->name, "=");
			str = ft_strjoin(str2, environ->value);
			printf("%s\n", str);
			free(str2);
			free(str);
		}
		environ = environ->next;
	}
}