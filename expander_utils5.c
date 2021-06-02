/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils5.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:21:38 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/02 09:01:44 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		strings_to_join(char **res, int i)
{
	if (((res[i][0] == '\'' && res[i][ft_strlen(res[i]) - 1] == '\'')
				|| (res[i][0] == '\"' && res[i][ft_strlen(res[i]) - 1] == '\"'))
			&& ft_strlen(res) > 2 && res[i + 1] && ft_strchr(res[i + 1], '='))
		return (1);
	else if (ft_strchr(res[i], '=') == 0 && res[i + 1] && res[i + 1][0] == '=')
		return (-1);
	return (0);
}

void	escaped_spaces_in_env(char *str, int *j, char ***tmp)
{
	char	**split;
	int		x;

	x = 0;
	if ((split = ft_split(str, " \t\n\r\v\f")))
	{
		while (split[x])
		{
			(*tmp)[*j] = ft_strdup(split[x]);
			(*j)++;
			x++;
		}
	}
	free(str);
	free_tabtab(split);
}

char	**create_parsed_res(char **res, t_list *var_env, t_command *cmd, char ***parsed_res)
{
	int		i;
	int		j;
	char	**tmp;
	char	*str;

	i = 0;
	j = 0;
	if (!(tmp = malloc(sizeof(char *) * 1000)))
		return (0);
	while (res[i])
	{
		if ((!(ft_strnstr(res[i], "\\$", ft_strlen(res[i])))) &&
		ft_strnstr(res[i], "$", ft_strlen(res[i])))
		{
			str = replace_by_env_value(ft_strdup(res[i]), var_env, cmd);
			escaped_spaces_in_env(str, &j, &tmp);
		}
		else
		{
			tmp[j] = antislashes_a_quotes(res[i]);
			j++;
		}
		i++;
	}
	free_tabtab(res);
	tmp[j] = NULL;
	if (!(*parsed_res = malloc(sizeof(char *) * (j + 1))))
		return (0);
	return (tmp);
}

char		*parsed_res_error(char **parsed_res, int j, t_command *cmd)
{
	char *tmp;

	tmp = NULL;
	if (parsed_res[j])
	{
		tmp = ft_strdup(parsed_res[j]);
		free(parsed_res[j]);
	}
	else
		tmp = ft_strdup("");
	return (tmp);
}

char	**last_command_rv(char **res, char **parsed_res)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (res[0][0] == '$' && res[0][1] == '?' && res[0][2] == '\0')
	{
		parsed_res[0] = ft_strdup("$?");
		parsed_res[1] = NULL;
		return (parsed_res);
	}
	return (NULL);
}
