/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:48:26 by user42            #+#    #+#             */
/*   Updated: 2021/05/05 15:47:14 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Functions that manage environment variables linked list - create, amend it
** & print it. Once the main variable list with environment variables imported
** from computer is created, it is amended with new entries if export is
** invoked, updated when unset is called, and printed when env is.
*/

#include "minishell.h"

void	name_a_value_var(char **name, char **value, char **env, int k)
{
	*name = ft_get_name(env[k]);
	*value = ft_strdup(&ft_strchr(env[k], '=')[1]);
}

t_list	*set_new_env(char **env, t_list *var_env, t_command *cmd)
{
	int		k;
	char	*name;
	char	*value;
	t_list	*tmp;

	k = 0;
	name = NULL;
	value = NULL;
	tmp = NULL;
	while (env[k + 1])
		k++;
	name_a_value_var(&name, &value, env, k);
	var_env = ft_lstnew(name, value);
	k--;
	while (k >= 0)
	{
		tmp = var_env;
		name = ft_get_name(env[k]);
		value = ft_strdup(&ft_strchr(env[k], '=')[1]);
		ft_lstadd_front(&var_env, ft_lstnew(name, value));
		ft_lstiter(var_env, &ft_record, cmd);
		tmp->prec = var_env;
		k--;
	}
	return (var_env);
}

void	set_env(char **tabl, t_list *var_env, t_command *cmd)
{
	int		i;
	int		j;
	t_list	*tmp_new;
	t_list	*tmp;

	j = 0;
	i = 0;
	tmp_new = NULL;
	tmp = NULL;
	while (tabl[j])
		j++;
	tmp = check_doublons(0, j, tabl, var_env);
	while (++i <= j - 1)
	{
		if (ft_strchr(tabl[i], '='))
		{
			tmp_new = ft_lstnew(ft_get_name(tabl[i]),
ft_strdup(&ft_strchr(tabl[i], '=')[1]));
			ft_lstadd_back(&var_env, tmp_new);
		}
		ft_lstiter(var_env, &ft_record, cmd);
		tmp->prec = tmp;
		tmp_new = tmp;
	}
}

void	unset(t_list *env, char **tabl)
{
	int		i;
	int		j;
	char	*name;

	name = NULL;
	i = 1;
	j = 0;
	while (tabl[j])
		j++;
	while (env)
	{
		while (i < j)
		{
			if (strcmp((name = ft_get_name(tabl[i])), env->name) == 0)
			{
				((char *)env->name)[0] = '\0';
				((char *)env->value)[0] = '\0';
			}
			i++;
			free(name);
		}
		env = env->next;
		i = 1;
	}
}

void	print_env(t_list *environ)
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
