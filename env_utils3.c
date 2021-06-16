/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:48:10 by user42            #+#    #+#             */
/*   Updated: 2021/06/16 07:15:52 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_i_value(char *tab_k, char *i_value)
{
	if (ft_strchr(tab_k, '='))
		i_value = ft_strdup(ft_strchr(tab_k, '='));
	else
		i_value = ft_strdup("");
	return (i_value);
}

char	*create_j_value(char *tab_l, char *j_value)
{
	if (ft_strchr(tab_l, '='))
		j_value = ft_strdup(ft_strchr(tab_l, '='));
	else
		j_value = ft_strdup("");
	return (j_value);
}

void	add_to_env_l(char **tabl, char *j_name, int k, int l)
{
	char	*i_value;
	char	*j_value;
	char	*tmp;

	i_value = create_i_value(tabl[k], i_value);
	j_value = create_i_value(tabl[l], j_value);
	tmp = ft_strdup(tabl[l]);
	if (ft_strchr(tmp, '+') && ft_strchr(tabl[k], '=') && \
	ft_strchr(tmp, '='))
	{
		free(tabl[l]);
		tabl[l] = join_a_free(join_a_free(join_a_free(j_name, \
		"="), &i_value[1]), &j_value[1]);
	}
	else
		free(j_name);
	free(tmp);
	free(i_value);
	free(j_value);
}

void	add_to_env_k(char **tabl, char *i_name, int k, int l)
{
	char	*i_value;
	char	*j_value;
	char	*tmp;

	i_value = create_i_value(tabl[k], i_value);
	j_value = create_i_value(tabl[l], j_value);
	tmp = ft_strdup(tabl[k]);
	if (ft_strchr(tmp, '+') && ft_strchr(tabl[l], '=') && \
	ft_strchr(tmp, '='))
	{
		free(tabl[k]);
		tabl[k] = join_a_free(join_a_free(join_a_free(i_name, \
		"="), &j_value[1]), &i_value[1]);
	}
	else
		free(i_name);
	free(tmp);
	free(i_value);
	free(j_value);
}
