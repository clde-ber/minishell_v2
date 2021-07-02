/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:14:05 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_free_set_args(char **args)
{
	int	k;

	k = 0;
	while (args[k])
		k++;
	ft_free(args, k + 1);
}

void	init_vars_set_args(int *index, int *k)
{
	*index = -1;
	*k = 0;
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
