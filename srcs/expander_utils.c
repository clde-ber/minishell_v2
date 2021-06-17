/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:21:38 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/17 15:43:57 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	strings_to_join(char **res, int i)
{
	if (((res[i][0] == '\'' && res[i][ft_strlen(res[i]) - 1] == '\'') \
	|| (res[i][0] == '\"' && res[i][ft_strlen(res[i]) - 1] == '\"')) \
	&& ft_strlen(res[i]) > 2 && res[i + 1] && ft_strchr(res[i + 1], '='))
		return (1);
	else if (ft_strchr(res[i], '=') == 0 && res[i + 1] && res[i + 1][0] == '=')
		return (-1);
	return (0);
}

char	**create_parsed_res(char **res)
{
	int		i;
	char	**parsed_res;

	parsed_res = NULL;
	i = 0;
	while (res[i])
	{
		res[i] = antislashes_a_quotes(res[i]);
		i++;
	}
	parsed_res = malloc(sizeof(char *) * (i + 1));
	if (!(parsed_res))
		return (0);
	return (parsed_res);
}

char	*parsed_res_error(char *res, char *parsed_res, t_list *var_env,
t_command *cmd)
{
	if (is_unknown_env_variable(res, var_env, cmd) && cmd->bol == 0)
	{
		free_string(parsed_res);
		return (NULL);
	}
	else
		parsed_res = remove_antislashes(parsed_res, res, var_env, cmd);
	return (parsed_res);
}

char	**last_command_rv(char **res, char **parsed_res)
{
	if (res[0][0] == '$' && res[0][1] == '?' && res[0][2] == '\0')
	{
		parsed_res[0] = ft_strdup("$?");
		parsed_res[1] = NULL;
		return (parsed_res);
	}
	return (NULL);
}

void	init_var_h_export(int *quotes, char **str_first, char **str_secd,
char **name)
{
	*quotes = 0;
	*str_first = NULL;
	*str_secd = NULL;
	*name = NULL;
}
