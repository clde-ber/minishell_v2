/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 07:43:03 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/11 07:49:12 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_back(char *str, int *j)
{
	int	k;

	k = 0;
	while (*j < ft_strlen(str) && (str[*j] == '/' \
	|| str[*j] == '.'))
	{
		while (str[*j] == '/')
			(*j)++;
		if (str[*j] == '.')
		{
			(*j)++;
			while (str[*j] == '.')
			{
				(*j)++;
				k++;
			}
		}
	}
	return (k);
}

void	path_copy(char **buf, int m, int k)
{
	int	i;

	i = ft_strlen(*buf) - 1;
	while (i > 0 && k >= 0)
	{
		if ((*buf)[i] == '/')
		{
			(*buf)[i] = '\0';
			k--;
		}
		i--;
	}
}

int	count_slash(char *old_pwd)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (i < ft_strlen(old_pwd))
	{
		if (old_pwd[i] == '/')
		{
			count++;
			i++;
		}
		while (old_pwd[i] == '/')
			i++;
		i++;
	}
	return (count);
}

void	cd_go_back(int *i, int k, char **buf, char *old_pwd)
{
	int	m;

	m = 0;
	m = ft_strrchr(*buf, '/');
	if (k < count_slash(old_pwd))
		path_copy(buf, m, k);
	else
	{
		free(*buf);
		*buf = ft_strdup("/");
	}
}

int	cd_go_front(char *res, int *i, int k, char **buf)
{
	int	index;
	int	count;

	count = 0;
	index = *i;
	if ((*buf)[ft_strlen(*buf) - 1] != '/')
		*buf = join_a_free(join_a_free(*buf, "/"), &res[index]);
	else
		*buf = join_a_free(*buf, &res[index]);
	while ((*buf)[count] && (*buf)[count] != '.')
		count++;
	while ((*buf)[count])
	{
		(*buf)[count] = '\0';
		count++;
	}
	while (res[*i] && res[*i] != '.')
		(*i)++;
}

void	set_pwd_env(char *path, char *buf, t_list *var_env)
{
	while (var_env->next)
	{
		if (ft_strcmp(var_env->name, "OLDPWD") == 0)
		{
			free(var_env->value);
			var_env->value = ft_strdup(path);
		}
		if (ft_strcmp(var_env->name, "PWD") == 0)
		{
			free(var_env->value);
			var_env->value = ft_strdup(buf);
		}
		var_env = var_env->next;
	}
}
