/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:14:05 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/09 14:13:09 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_set_args(char **args, char **n_res)
{
	int	k;

	k = 0;
	while (args[k])
		k++;
	ft_free(args, k + 1);
	free_tabtab(n_res);
}

void	init_vars_set_args(int *index, int *k, char ***n_res, char **res)
{
	*index = -1;
	*k = 0;
	*n_res = new_res(res);
}

void	init_2_vars(int *i, int *k)
{
	*i = 0;
	*k = 0;
}

int	command_not_found(char **tabl, char **env, char **p_bin)
{
	free(tabl[0]);
	free_tabtab(env);
	free_tabtab(p_bin);
	return (1);
}

int	command_found(char **tabl, char **env, char **p_bin)
{
	free(tabl[0]);
	free_tabtab(env);
	free_tabtab(p_bin);
	return (0);
}
