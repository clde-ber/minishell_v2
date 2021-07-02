/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:48:26 by user42            #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Functions that manage environment variables linked list - create, amend it
** & print it. Once the main variable list with environment variables imported
** from computer is created, it is amended with new entries if export is
** invoked, updated when unset is called, and printed when env is.
*/

#include "../includes/minishell.h"

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

void	reset_cmd_path(t_list *lst, t_command *cmd)
{
	int	boolean;

	boolean = 0;
	while (lst)
	{
		if (strcmp(lst->name, "PATH") == 0)
		{
			if (cmd->path)
			{
				free(cmd->path);
				cmd->path = NULL;
			}
			cmd->path = ft_strdup(lst->value);
			boolean = 1;
		}
		lst = lst->next;
	}
	if (boolean == 0)
	{
		if (cmd->path)
		{
			free(cmd->path);
			cmd->path = ft_strdup("");
		}
	}
}

void	set_env(char **tabl, t_list *var_env, t_command *cmd, int j)
{
	int		i;
	t_list	*tmp_new;
	t_list	*tmp;
	char	*name;

	i = 0;
	init_strings_set_env(&tmp_new, &tmp, &name);
	while (++i < j)
	{
		tmp = check_doublons(0, j, tabl, var_env);
		if (ft_strchr(tabl[i], '='))
		{
			name = ft_get_name(tabl[i]);
			if (is_valid_env_name(name))
			{
				tmp_new = ft_lstnew(ft_get_name(tabl[i]), \
				ft_strdup(&ft_strchr(tabl[i], '=')[1]));
				ft_lstadd_back(&var_env, tmp_new);
			}
			free(name);
		}
		ft_lstiter(var_env, &ft_record, cmd);
		var_env->prec = tmp;
	}
	var_env = tmp_new;
}

void	unset(t_list *env, char **tabl, t_command *cmd, int j)
{
	int		i;
	char	*name;
	int		boolean;

	init_vars_unset(&name, &i, &boolean);
	while (env)
	{
		while (i < j)
		{
			name = ft_get_name(tabl[i]);
			if (ft_strcmp(name, env->name) == 0)
			{
				((char *)env->name)[0] = '\0';
				((char *)env->value)[0] = '\0';
			}
			i++;
			free(name);
		}
		if (record_cmd_path(env, cmd) == 1)
			boolean = 1;
		env = env->next;
		i = 1;
	}
	unset_cmd_path(boolean, cmd);
}

void	print_env(t_list *environ, t_command *cmd)
{
	char	*name;
	char	*value;

	name = NULL;
	value = NULL;
	while (environ)
	{
		if (ft_strlen(environ->name))
		{
			name = ft_strjoin(environ->name, "=");
			value = ft_strjoin(name, environ->value);
			ft_putstr_fd(value, 1);
			ft_putstr_fd("\n", 1);
			free(value);
			free(name);
		}
		environ = environ->next;
	}
	cmd->cmd_rv = 0;
}
