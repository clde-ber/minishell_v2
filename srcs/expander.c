/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:25 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/10 08:41:03 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*
** Functions that play the role of the expander. After all the arguments in
** the command line have been splited with ft_split, each argument is read
** according to whether it begins with ' " $ or whatever. A two dimensional
** array is returned to be used either in the fonctions that are shell commands
** recreated builtins or in the execve function.
*/

char	*expander(char *res, t_list *var_env, char **args, t_command *cmd)
{
	cmd->index = 0;
	if (is_handled_cmd(args[0]) == 0 || ft_strcmp(args[0], "echo") == 0
		|| ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "cd") == 0)
		return (non_handled_commands(res, var_env, cmd));
	else if (((ft_strcmp(args[0], "export") == 0 && ft_strcmp(res, "export"))
			|| (ft_strcmp(args[0], "unset") == 0 && ft_strcmp(res, "unset"))))
	{
		if (ft_strcmp(args[0], "export") == 0 && ft_strcmp(res, "export"))
			return (handled_export(res, var_env, cmd));
		else if (ft_strcmp(args[0], "unset") == 0 && ft_strcmp(res, "unset"))
			return (handled_unset(res, var_env, cmd));
	}
	return (ft_strdup(res));
}

void	init_vars_parse_res(int *i, int *j, char **str)
{
	*i = -1;
	*j = 0;
	*str = NULL;
}

void	inc_j(char **parsed_res, int *j)
{
	if (parsed_res[*j])
		(*j)++;
}

char	**parse_res(char **res, t_list *var_env, t_command *cmd)
{
	int		i;
	char	**parsed_res;
	int		j;
	char	*str;

	init_vars_parse_res(&i, &j, &str);
	parsed_res = create_parsed_res(res);
	while (res[++i])
	{
		if ((strings_to_join(res, i)) > 0)
		{
			str = ft_strjoin(res[i], res[i + 1]);
			i++;
			parsed_res[j] = expander(str, var_env, res, cmd);
			free_string(str);
		}
		else
			parsed_res[j] = expander(res[i], var_env, res, cmd);
		parsed_res[j] = parsed_res_error(res[i], parsed_res[j], var_env, cmd);
		inc_j(parsed_res, &j);
		parsed_res[j] = NULL;
	}
	return (parsed_res);
}
