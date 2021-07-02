/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:48:10 by user42            #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

	init_i_a_j_values(&i_value, &j_value, tabl[k], tabl[l]);
	tmp = ft_strdup(tabl[l]);
	if (ft_strchr(tmp, '+') && ft_strchr(tabl[k], '=') && \
	ft_strchr(tabl[k], '+') && ft_strchr(tmp, '='))
		plus_equal(&tabl[l], j_name, i_value, j_value);
	else if (ft_strchr(tmp, '+') && ft_strchr(tabl[k], '=') && \
	ft_strchr(tmp, '='))
		equal(&tabl[l], j_name, i_value, j_value);
	else if (ft_strchr(tmp, '='))
	{
		free(tabl[l]);
		tabl[l] = join_a_free(join_a_free(j_name, "="), &j_value[1]);
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

	init_i_a_j_values(&i_value, &j_value, tabl[k], tabl[l]);
	tmp = ft_strdup(tabl[k]);
	if (ft_strchr(tmp, '+') && ft_strchr(tabl[l], '=') && \
	ft_strchr(tabl[l], '+') && ft_strchr(tmp, '='))
		plus_equal(&tabl[k], i_name, j_value, i_value);
	else if (ft_strchr(tmp, '+') && ft_strchr(tabl[l], '=') && \
	ft_strchr(tmp, '='))
		equal(&tabl[k], i_name, j_value, i_value);
	else if (ft_strchr(tmp, '='))
	{
		free(tabl[k]);
		tabl[k] = join_a_free(join_a_free(i_name, "="), &i_value[1]);
	}
	else
		free(i_name);
	free(tmp);
	free(i_value);
	free(j_value);
}

void	set_i_a_j_name(char **i_name, char **j_name, char **split, char \
**split2)
{
	if (split[0])
		*i_name = ft_get_name(split[0]);
	else
		*i_name = ft_strdup("");
	if (split2[0])
		*j_name = ft_get_name(split2[0]);
	else
		*j_name = ft_strdup("");
	free_tabtab(split);
	free_tabtab(split2);
}
