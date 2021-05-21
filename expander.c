/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:25 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/21 03:50:28 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Functions that play the role of the expander. After all the arguments in
** the command line have been splited with ft_split, each argument is read
** according to whether it begins with ' " $ or whatever. A two dimensional
** array is returned to be used either in the fonctions that are shell commands
** recreated builtins or in the execve function.
*/

char	*handled_unset(char *res, t_list *var_env, t_command *cmd)
{
	char	*trim;
	char	*trim2;
	int		quotes;

	quotes = 0;
	trim = NULL;
	trim2 = NULL;
	cmd->index = 0;
	trim = ft_strtrim(res, "\"");
	if (is_valid_env_name(res))
	{
		if (ft_strlen(trim) != ft_strlen(res))
			quotes = 1;
		if (quotes == 0 && ft_strchr(trim, '\"') == 0 && ft_strchr(trim, '\'') == 0)
			trim = replace_by_env(trim, var_env, cmd, 0);
		if (trim && ft_strchr(trim, '\"') == 0 && ft_strchr(trim, '\'') == 0)
			return (trim);
	}
	cmd->cmd_rv = 1;
	write(1, "bash: unset: '", 15);
	trim2 = ft_strtrim(trim, "\'");
	if (quotes == 0)
		write(1, trim2, ft_strlen(trim2));
	else
		write(1, trim, ft_strlen(trim));
	write(1, "': not a valid identifier\n", 26);
	free(trim);
	free(trim2);
	return (NULL);
}

char	*expander(char *res, t_list *var_env, char **args, t_command *cmd)
{
	char	*trim;
	char	*str;
	int		quotes;

	quotes = 0;
	trim = NULL;
	str = NULL;
	cmd->index = 0;
	if (is_handled_cmd(args[0]) == 0 || ft_strcmp(args[0], "echo") == 0 ||
			ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "cd") == 0)
		return (non_handled_commands(res, var_env, cmd));
	else if (ft_strcmp(args[0], "export") == 0 && ft_strcmp(res, "export") ||
	ft_strcmp(args[0], "unset") == 0 && ft_strcmp(res, "unset"))
	{
		if (ft_strcmp(args[0], "export") == 0 && ft_strcmp(res, "export"))
			return (handled_export(res, var_env, cmd));
		else if (ft_strcmp(args[0], "unset") == 0 && ft_strcmp(res, "unset"))
			return (handled_unset(res, var_env, cmd));
	}
	return (ft_strdup(res));
}

char	**parse_res(char **res, t_list *var_env, t_command *cmd)
{
	int		i;
	char	**parsed_res;
	int		j;

	i = 0;
	j = 0;
	parsed_res = create_parsed_res(res);
	if (last_command_rv(res, parsed_res))
		return (parsed_res);
	while (res[i])
	{
		if ((strings_to_join(res, i)) > 0)
			parsed_res[j] = expander(ft_strjoin(res[i],
						res[++i]), var_env, res, cmd);
		else if ((strings_to_join(res, i)) == -1)
			parsed_res[j] = ft_strdup("");
		else
			parsed_res[j] = expander(res[i], var_env, res, cmd);
		if (parsed_res_error(parsed_res, j))
			parsed_res[j] = ft_strdup("");
		printf("parsed_res %s\n", parsed_res[j]);
		i++;
		j++;
	}
	parsed_res[j] = NULL;
	return (parsed_res);
}
