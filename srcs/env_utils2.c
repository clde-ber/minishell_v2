/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:54:50 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Functions that output a two dimensional array for environment values, sort it
** and print it.
*/

#include "../includes/minishell.h"

void	init_vars_fill_list(int *i, t_list **environ, t_list **tmp)
{
	*tmp = *environ;
	*i = 0;
}

char	**fill_list(t_list *environ, char **list, int i)
{
	t_list	*tmp;

	init_vars_fill_list(&i, &environ, &tmp);
	while (environ->next)
	{
		environ = environ->next;
		i++;
	}
	list = malloc(sizeof(char *) * (i + 3));
	if (!(list))
		return (0);
	i = 0;
	while (tmp)
	{
		if (ft_strlen(tmp->name))
		{
			list[i] = join_a_free(join_a_free(join_a_free(join_a_free(\
			ft_strjoin("declare -x ", tmp->name), "="), "\""), tmp->value), \
			"\"");
			i++;
		}
		tmp = tmp->next;
	}
	list[i] = NULL;
	return (list);
}

char	**sort_list(char **list, int i, int j)
{
	char	*tmp;
	char	*i_name;
	char	*j_name;

	tmp = NULL;
	i_name = NULL;
	j_name = NULL;
	while (list[++i])
	{
		while (list[++j])
		{
			i_name = ft_get_name(list[i]);
			j_name = ft_get_name(list[j]);
			if (strcmp(i_name, j_name) < 0)
			{
				tmp = list[i];
				list[i] = list[j];
				list[j] = tmp;
			}
			free(i_name);
			free(j_name);
		}
		j = -1;
	}
	return (list);
}

void	print_sorted_env(t_list *environ, t_command *cmd)
{
	char	**list;
	int		i;
	int		j;

	i = -1;
	j = -1;
	list = NULL;
	list = fill_list(environ, list, i);
	list = sort_list(list, i, j);
	while (list[++i])
	{
		ft_putstr_fd(list[i], 1);
		ft_putstr_fd("\n", 1);
	}
	ft_free(list, i + 1);
	list = NULL;
	cmd->cmd_rv = 0;
}

int	is_valid_env_name(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '\0')
		return (0);
	if (str[i] == '+' || str[i] == '=')
		return (0);
	while (i < (int)ft_strlen(str))
	{
		if (i < (int)ft_strlen(str) && !(str[i] == '_' || ft_isalnum(str[i]) \
		|| ((str[i] == '=' || str[i] == '+') && ft_strlen(str) > 1)))
			return (0);
		i++;
	}
	return (1);
}
