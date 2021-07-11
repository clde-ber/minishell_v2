/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 16:47:50 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/11 10:55:51 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	split_execve_args(char ***new_res, char **tmp, int *x, int *j)
{
	(*new_res)[*j] = ft_strdup(tmp[*x]);
	(*x)++;
	(*j)++;
}

void	no_split_execve_args(char ***new_res, char **res, int i, int *j)
{
	(*new_res)[*j] = ft_strdup(res[i]);
	(*j)++;
}

void	init_vars_new_res(int *i, int *j, int *x, char ***tmp)
{
	*i = -1;
	*j = 0;
	*x = 0;
	*tmp = NULL;
}

char	**new_res(char **res)
{
	int		i;
	int		j;
	int		x;
	char	**tmp;
	char	**new_res;

	init_vars_new_res(&i, &j, &x, &tmp);
	new_res = malloc(sizeof(char *) * 1000);
	if (!(new_res))
		return (ft_calloc(2, sizeof(char *)));
	while (res[++i])
	{
		tmp = ft_split(res[i], " \t\n\r\v\f");
		if (tmp[0] && is_handled_cmd(tmp[0]) == 0)
		{
			while (tmp[x])
				split_execve_args(&new_res, tmp, &x, &j);
		}
		else
			no_split_execve_args(&new_res, res, i, &j);
		x = 0;
		free_tabtab(tmp);
	}
	new_res[j] = NULL;
	return (new_res);
}

int	len_tab(char **res)
{
	int	i;

	i = 0;
	while (res[i])
		i++;
	return (i);
}
