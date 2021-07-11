/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_values_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 14:30:34 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/11 10:29:34 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*get_string_value(char *str, int boolean, char *trim, int x)
{
	int		i;
	char	*res;

	i = 0;
	res = NULL;
	res = malloc(sizeof(char) * (ft_strlen(str) + 1));
	(void)boolean;
	if (!(res))
		return (0);
	while (str[i] && (((((i && str[i] == '\\' && str[i + 1] == '$') || \
	(i && str[i - 1] == '\\' && str[i] == '$')) || ((i == 0 && str[i] == '$') \
	&& !(ft_isalnum(str[i]) || str[i] == '_' || str[i] == '?')) \
	|| str[i] != '$' || \
	((is_in_sq_string(x + (int)i, trim) && is_in_sq_string(x + (int)i, trim) \
	% 2) && !(is_in_dq_string((int)i + x, trim) && \
	is_in_dq_string((int)i + x, trim) % 2)) || (str[i] == '$' && str[i + 1] \
	== '?' && is_command_return_value(i, str) == 0)))))
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

int	is_command_return_value(int i, char *buf)
{
	if ((((!is_in_sq_string(i, buf) || \
	is_in_sq_string(i, buf) % 2 == 0) || (is_in_sq_string(i, buf) && \
	is_in_sq_string(i, buf) % 2 && is_in_dq_string(i, buf) && \
	is_in_dq_string(i, buf) % 2 && ft_strchr(buf, '\'') && \
	ft_strchr(buf, '\"') && ft_strchr_bis(buf, '\'') > \
	ft_strchr_bis(buf, '\"')))) && (i == 0 || (i && buf[i - 1] != '\\')))
		return (1);
	return (0);
}

char	*get_env_value_name(char *str, t_list *var_env, t_command *cmd)
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
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
	{
		test[i] = str[i];
		i++;
		test[i] = '\0';
		free_string(ret);
		ret = search_env_value(test, var_env);
	}
	cmd->index += ft_strlen(test) + 1;
	free(test);
	return (ret);
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
	while (str[i] && ((ft_strcmp(ret, "") == 0 && (ft_isalnum(str[i]) || \
	str[i] == '_')) || str[i] == '?'))
	{
		if (str[i] == '?')
			return (cmd_return_value(&ret, cmd, &test));
		test[i] = str[i];
		i++;
		test[i] = '\0';
		free_string(ret);
		ret = search_env_value(test, var_env);
	}
	cmd->index += ft_strlen(test) + 1;
	free(test);
	return (ret);
}
