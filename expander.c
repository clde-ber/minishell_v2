/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:25 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/04 07:32:52 by clde-ber         ###   ########.fr       */
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
	char *trim;
	int bool1;

	bool1 = 0;
	trim = NULL;
	if (ft_strlen(ft_strtrim(res, "\"")) != ft_strlen(res))
		bool1 = 1;
	trim = ft_strtrim(res, "\"");
	if (bool1 == 0 && ft_strchr(trim, '\"') == 0 && ft_strchr(trim, '\'') == 0)
		trim = replace_by_env(trim, var_env, cmd, 0);
	if (trim && ft_strchr(trim, '\"') == 0 && ft_strchr(trim, '\'') == 0)
		return (trim);
	else
	{
		cmd->cmd_rv = 1;
		write(1, "bash: export: '", 16);
		if (bool1 == 0)
			write(1, ft_strtrim(trim, "\'"), ft_strlen(ft_strtrim(trim, "\'")));
		else
			write(1, trim, ft_strlen(trim));
		write(1, "': not a valid identifier\n", 26);
		return (ft_strdup(""));
	}
}

char	*expander(char *res, t_list *var_env, char **args, t_command *cmd)
{
	char	*trim;
	char	*name;
	char	*str;
	int		bool1;

	bool1 = 0;
	trim = NULL;
	name = NULL;
	str = NULL;
	cmd->index = 0;
	if (is_handled_cmd(args[0]) == 0 || ft_strcmp(args[0], "echo") == 0 ||
			ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "cd") == 0)
		return (non_handled_commands(res, var_env, cmd));
	else
	{
		if (ft_strcmp(args[0], "export") == 0 && ft_strcmp(res, "export"))
			return (handled_export(res, var_env, cmd));
		else if (ft_strcmp(args[0], "unset") == 0 && ft_strcmp(res, "unset"))
			return (handled_unset(res, var_env, cmd));
	}
	return (ft_strdup(res));
}

int		strings_to_join(char **res, int i)
{
	if (((res[i][0] == '\'' && res[i][ft_strlen(res[i]) - 1] == '\'')
				|| (res[i][0] == '\"' && res[i][ft_strlen(res[i]) - 1] == '\"'))
			&& res[i + 1] && ft_strchr(res[i + 1], '='))
		return (1);
	else if (ft_strchr(res[i], '=') == 0 && res[i + 1] && res[i + 1][0] == '=')
		return (-1);
	return (0);
}

char	**create_parsed_res(char **res)
{
	int		i;
	char	**tmp;
	char	**parsed_res;

	parsed_res = NULL;
	i = 0;
	while (res[i])
	{
		res[i] = antislashes_a_quotes(res[i]);
		i++;
	}
	if (!(parsed_res = malloc(sizeof(char *) * (i + 1))))
		return (0);
	return (parsed_res);
}

char	**parse_res(char **res, t_list *var_env, t_command *cmd)
{
	int		i;
	char	**parsed_res;
	int		j;

	parsed_res = create_parsed_res(res);
	if (res[0][0] == '$' && res[0][1] == '?' && res[0][2] == '\0')
	{
		parsed_res[0] = ft_strdup("$?");
		parsed_res[1] = NULL;
		return (parsed_res);
	}
	i = 0;
	j = 0;
	while (res[i])
	{
		if ((strings_to_join(res, i)) > 0)
		{
			parsed_res[j] = expander(ft_strjoin(res[i],
						res[i + 1]), var_env, res, cmd);
			i++;
		}
		else if ((strings_to_join(res, i)) == -1)
			parsed_res[j] = NULL;
		else
			parsed_res[j] = expander(res[i], var_env, res, cmd);
		if (parsed_res[j] == NULL)
		{
			ft_free(parsed_res, j + 1);
			return (NULL);
		}
		printf("parsed_res %s\n", parsed_res[j]);
		i++;
		j++;
	}
	parsed_res[j] = NULL;
	return (parsed_res);
}
