/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:30:34 by clde-ber          #+#    #+#             */
/*   Updated: 2021/04/28 16:22:42 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_string(char *str)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	if (!(res = malloc(sizeof(char) * (ft_strlen(str) + 1))))
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
	if (!(res = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (0);
	while (str[i] && str[i] != '$')
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

	i = 0;
	if (!(test = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (0);
	test[i] = '\0';
	while (str[i] && ft_strcmp((ret = search_env_value(
	test, var_env)), "") == 0)
	{
		test[i] = str[i];
		i++;
		test[i] = '\0';
		free(ret);
		ret = 0;
	}
	if (ret)
	{
		free(ret);
		ret = 0;
	}
	if (ft_strcmp((ret = search_env_value(test, var_env)), "") == 0)
	{
		free(ret);
		ret = ft_strdup("");
		free(test);
		return (ret);
	}
	else
	{
		cmd->index += ft_strlen(test);
		free(test);
		return (ret);
	}
}

char	*get_env(char *str, t_list *var_env, t_command *cmd)
{
	int		i;
	char	*test;
	char	*ret;

	i = 0;
	if (!(test = malloc(sizeof(char) * (ft_strlen(str) + 1))))
		return (0);
	test[i] = '\0';
	while (str[i] && ft_strcmp((ret = search_env_value(test,
	var_env)), "") == 0)
	{
		test[i] = str[i];
		i++;
		test[i] = '\0';
		free(ret);
		ret = 0;
	}
	if (ret)
	{
		free(ret);
		ret = 0;
	}
	if (ft_strcmp((ret = search_env_value(test, var_env)), "") == 0)
	{
		free(ret);
		ret = ft_strdup("");
		cmd->index += ft_strlen(test);
		free(test);
		return (ret);
	}
	else
	{
		cmd->index += ft_strlen(test);
		free(test);
		return (ret);
	}
}
