/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:30:34 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/16 11:36:44 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_string(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(res))
		return (0);
	while (str[i] && is_valid_env_c(str[i]))
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_string_value(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(res))
		return (0);
	while (str[i] && ((str[i] == '\\' && str[i + 1] == '$') || (i && str[i - 1] \
		== '\\' && str[i] == '$') || str[i] != '$'))
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_env_value(char *str, t_list *var_env, t_command *cmd)
{
	int		i;
	char	*test;
	char	*ret;

	init_vars_get_env_v(&i, &ret);
	test = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(test))
		return (0);
	test[i] = '\0';
	ret = search_env_value(test, var_env);
	while (str[i] && ft_strcmp(ret, "") == 0 && ((str[i] != '$') \
		&& (!(str[i] == '\\' && str[i + 1] == '$'))) && str[i] != '\"' \
		&& str[i] != '\'')
	{
		test[i] = str[i];
		i++;
		test[i] = '\0';
		free_string(ret);
		ret = search_env_value(test, var_env);
	}
	free_string(ret);
	ret = search_env_value(test, var_env);
	cmd->index += ft_strlen(test) + 1;
	free(test);
	return (ret);
}

int	even_or_odd(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] == '\'')
		i++;
	return (i);
}

char	*find_op(char *str)
{
	int		i;
	char	*ret;

	i = 0;
	ret = NULL;
	if (ft_strchr(str, '=') && ft_strlen(str) > 1)
	{
		ret = ft_strchr(str, '=');
		return ("=");
	}
	else
		return ("");
}
