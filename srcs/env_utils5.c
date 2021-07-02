/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 09:28:32 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_i_a_j_values(char **i_value, char **j_value, char *tabl_k,
char *tabl_l)
{
	*i_value = NULL;
	*j_value = NULL;
	*i_value = create_i_value(tabl_k, *i_value);
	*j_value = create_i_value(tabl_l, *j_value);
}

void	plus_equal(char **tabl, char *x_name, char *a_value, char *b_value)
{
	free(*tabl);
	*tabl = join_a_free(join_a_free(join_a_free(x_name, \
	"+="), &a_value[1]), &b_value[1]);
}

void	equal(char **tabl, char *x_name, char *a_value, char *b_value)
{
	free(*tabl);
	*tabl = join_a_free(join_a_free(join_a_free(x_name, \
	"="), &a_value[1]), &b_value[1]);
}
