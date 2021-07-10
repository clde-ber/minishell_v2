/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 11:04:24 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/10 15:49:57 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	set_list_mp(t_test **start, t_fd *f)
{
	int	j;

	j = 1;
	while (j <= count_pipes(f->res))
	{
		ft_lstadd_back2(start, ft_lstnew2(middle_pipe(f->res, j)));
		j++;
	}
}

void	init_mul(t_mult *mul, t_list *var_env, t_fd *f, char **env)
{
	mul->var_e = var_env;
	mul->f = &f;
	mul->env = &env;
	g_sig.boolean = 2;
}
