/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:25 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/02 09:00:42 by clde-ber         ###   ########.fr       */
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

void	write_error(char *trim, int quotes, t_command *cmd)
{
	char *str;

	if (trim[0] == '\'')
		str = ft_strtrim(trim, "\'");
	else
		str = ft_strdup(trim);
	write(1, "bash: unset: '", 15);
	if (quotes == 0)
		write(1, str, ft_strlen(str));
	else
		write(1, trim, ft_strlen(trim));
	write(1, "': not a valid identifier\n", 26);
	cmd->cmd_rv = 1;
	free(trim);
	free(str);
}

char	*handled_unset(char *res, t_list *var_env, t_command *cmd)
{
	char	*trim;
	char	*trim2;
	int		quotes;

	quotes = 0;
	trim2 = NULL;
	cmd->index = 0;
	if (res[0] == '\"')
		trim = ft_strtrim(res, "\"");
	else
		trim = ft_strdup(res);
	if (ft_strlen(trim) != ft_strlen(res))
		quotes = 1;
	if (((quotes == 0 && ft_strchr(trim, '\"') == 0) ||
	(quotes == 1 && ft_strchr(trim, '\'') == 0)) && ft_strcmp(trim, ""))
	{
		if (trim[0] == '\'')
			trim2 = ft_strtrim(trim, "\'");
		else
			trim2 = ft_strdup(trim);
		free(trim);
		if (ft_strcmp(trim = antislashes_dolls(replace_by_env(trim2, var_env, cmd, 0)), "") == 0)
		{
			free(trim);
			return (NULL);
		}
	}
	cmd->cmd_rv = 1;
	if (!(is_valid_env_name(trim)))
	{
		write_error(trim, quotes, cmd);
		return (NULL);
	}
	return (trim);
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
	else if (((ft_strcmp(args[0], "export") == 0 && ft_strcmp(res, "export"))
	|| (ft_strcmp(args[0], "unset") == 0 && ft_strcmp(args, "unset"))) &&
	chrtabtab(args, "|") == -1 && chrtabtab(args, ">") == -1 && chrtabtab(args, "<")
	== -1 && chrtabtab(args, ">>") == -1)
	{
		if (ft_strcmp(args[0], "export") == 0 && ft_strcmp(res, "export"))
			return (handled_export(res, var_env, cmd));
		else if (ft_strcmp(args[0], "unset") == 0 && ft_strcmp(res, "unset"))
			return (handled_unset(res, var_env, cmd));
	}
	return (ft_strdup(res));
}

void	remove_empty_string(char *str, int *j)
{
	if (ft_strcmp(str, "") == 0)
	{
		free(str);
		(*j)--;
	}
}


char	**parse_res(char **res, t_list *var_env, t_command *cmd)
{
	int		i;
	char	**parsed_res;
	int		j;
	char	**new_res;

	i = -1;
	j = 0;
	new_res = create_parsed_res(res, var_env, cmd, &parsed_res);
	if (last_command_rv(new_res, parsed_res))
		return (parsed_res);
	while (new_res[++i])
	{
		if (ft_strcmp(new_res[j], "$?") == 0)
			parsed_res[j] = rv_itoa(cmd->cmd_rv);
		else if ((strings_to_join(new_res, i)) > 0)
			parsed_res[j] = expander(ft_strjoin(new_res[i],
						new_res[++i]), var_env, new_res, cmd);
		else if ((strings_to_join(new_res, i)) == -1)
			parsed_res[j] = ft_strdup("");
		else
			parsed_res[j] = expander(new_res[i], var_env, new_res, cmd);
		
		parsed_res[j] = parsed_res_error(parsed_res, j, cmd);
//		remove_empty_string(parsed_res[j], &j);
		j++;
	}
	free_tabtab(new_res);
	parsed_res[j] = NULL;
	return (parsed_res);
}
