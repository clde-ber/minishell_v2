/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:54:39 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Functions that help managing environment variables linked list. Output
** variable name, check whether there are doublons in environement variable
** names in the command line itself or compare new variables names with
** existing ones. If so, variable values are replaced by the last one that are
** set. If += symbols, associated env varibale value is added to existing one.
*/

char	*ft_get_name(char *str)
{
	int		i;
	char	*copy;

	i = 0;
	copy = ft_strdup(str);
	while (copy[i])
	{
		if (copy[i] == '=' || (copy[i] == '+' && copy[i + 1] == '=') || \
		(copy[i] == '+' && copy[i + 1] == '\0'))
		{
			copy[i] = '\0';
			return (copy);
		}
		i++;
	}
	return (copy);
}

void	add_to_env(char **tabl, int k, int l)
{
	char	*i_name;
	char	*j_name;
	char	**split;
	char	**split2;

	split = parse_path(tabl[k], '=');
	split2 = parse_path(tabl[l], '=');
	set_i_a_j_name(&i_name, &j_name, split, split2);
	if (l > k)
	{
		add_to_env_l(tabl, j_name, k, l);
		tabl[k][0] = '\0';
		free(i_name);
	}
	else if (l < k)
	{
		add_to_env_k(tabl, i_name, k, l);
		tabl[l][0] = '\0';
		free(j_name);
	}
	else
	{
		free(i_name);
		free(j_name);
	}
}

void	check_doublons_cl(char **tabl, char *i_name, char *j_name, int j)
{
	int	k;
	int	l;

	while (tabl[j])
		j++;
	k = 1;
	l = 1;
	while (k < j)
	{
		while (l < j)
		{
			i_name = ft_get_name(tabl[k]);
			j_name = ft_get_name(tabl[l]);
			if (ft_strcmp(i_name, j_name) == 0)
				add_to_env(tabl, k, l);
			free(i_name);
			free(j_name);
			l++;
		}
		l = 1;
		k++;
	}
}

t_list	*check_doublons(int k, int j, char **tabl, t_list *var_env)
{
	k = 1;
	while (var_env->next)
	{
		while (k < j)
		{
			replace_env(tabl[k], var_env);
			k++;
		}
		k = 1;
		var_env = var_env->next;
	}
	k = 1;
	while (k < j)
	{
		replace_env(tabl[k], var_env);
		k++;
	}
	return (var_env);
}

void	replace_env(char *tabl, t_list *var_env)
{
	char	**name;
	char	*name_var;

	name_var = NULL;
	name = parse_path(tabl, '=');
	if (name[0])
		name_var = ft_get_name(name[0]);
	if (name[0] && ft_strcmp(name_var, var_env->name) == 0)
	{
		if (ft_strchr(tabl, '+'))
		{
			var_env->value = join_a_free(var_env->value, \
			&ft_strchr(tabl, '=')[1]);
		}
		else if (ft_strchr(tabl, '='))
		{
			free(var_env->value);
			var_env->value = ft_strdup(&ft_strchr(tabl, '=')[1]);
		}
		tabl[0] = '\0';
	}
	free_tabtab(name);
	free_string(name_var);
}
