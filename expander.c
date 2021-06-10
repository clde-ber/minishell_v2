/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:25 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/10 15:33:57 by clde-ber         ###   ########.fr       */
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

char	*write_error(char *trim, char *trim2, int quotes, t_command *cmd)
{
	char	*str;

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
	free_string(trim);
	free_string(trim2);
	free_string(str);
	return (NULL);
}

void	if_d_quotes_unset(char **trim, char *res, int *quotes)
{
	if (res[0] == '\"')
		*trim = ft_strtrim(res, "\"");
	else
		*trim = ft_strdup(res);
	if (ft_strlen(*trim) != ft_strlen(res))
		*quotes = 1;
}

void	if_s_quotes_unset(char *trim, char **trim2)
{
	if (trim[0] == '\'')
		*trim2 = ft_strtrim(trim, "\'");
	else
		*trim2 = ft_strdup(trim);
}

char	*handled_unset(char *res, t_list *var_env, t_command *cmd)
{
	char	*trim;
	char	*trim2;
	int		quotes;

	init_2_strings(trim, trim2);
	init_2_vars(&quotes, &cmd->index);
	if_d_quotes_unset(&trim, res, &quotes);
	if (((quotes == 0 && ft_strchr(trim, '\"') == 0) || (quotes == 1
				&& ft_strchr(trim, '\'') == 0)) && ft_strcmp(trim, ""))
	{
		if_s_quotes_unset(trim, &trim2);
		free_string(trim);
		trim = replace_by_env_value(trim2, var_env, cmd);
	}
	trim2 = ft_strdup(trim);
	if (!(is_valid_env_name(trim)))
		return (write_error(trim, trim2, quotes, cmd));
	free_string(trim2);
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
	if (is_handled_cmd(args[0]) == 0 || ft_strcmp(args[0], "echo") == 0
		|| ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "cd") == 0)
		return (non_handled_commands(res, var_env, cmd));
	else if (((ft_strcmp(args[0], "export") == 0 && ft_strcmp(res, "export"))
			|| (ft_strcmp(args[0], "unset") == 0 && ft_strcmp(args, "unset"))))
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

int	condition_one(int i, char *dest, char *str, char *env)
{
	if (i < ft_strlen(dest) && (((i && dest[i - 1] != '\\') || i == 0) && \
		((((str[0] == '$' && (!(ft_strchr(env, '\"')))) || str[0] != '$') && \
		(dest[i] == '\"' && dest[ft_strlen(dest) - 1 - i] != '\"')) || \
		(((str[0] == '$' && (!(ft_strchr(env, '\'')))) || str[0] != '$') && \
		(dest[i] == '\'' && dest[ft_strlen(dest) - 1 - i] != '\'')))))
		return (1);
	return (0);
}

int	condition_two(int i, char *dest)
{
	if (i < ft_strlen(dest) && dest[i] == '\\' && (dest[i + 1] == '\\' \
		|| dest[i + 1] == '|' || dest[i + 1] == ';' || dest[i + 1] == '>' \
		|| dest[i + 1] == '<' || dest[i + 1] == '\'' || dest[i + 1] == '\"'))
		return (1);
	return (0);
}

char	*remove_antislashes(char *dest, char *str, t_list *var_env,
t_command *cmd)
{
	int		i;
	int		j;
	char	*res;
	char	*env;

	init_2_vars(&i, &j);
	env = replace_by_env(ft_strdup(str), var_env, cmd);
	res = malloc(sizeof(char) * (ft_strlen(dest) + 1));
	if (!(res))
		return (0);
	while (i < ft_strlen(dest))
	{
		if (condition_one(i, dest, str, env))
		{
			while (dest[i] && (dest[i] == '\'' || dest[i] == '\"'))
				i++;
		}
		else if (condition_two(i, dest))
			i++;
		else if (i < ft_strlen(dest))
			fill_string(&i, &j, dest, &res);
	}
	res[j] = '\0';
	ft_free_2_strings(dest, env);
	return (res);
}

char	**parse_res(char **res, t_list *var_env, t_command *cmd)
{
	int		i;
	char	**parsed_res;
	int		j;

	i = -1;
	j = 0;
	parsed_res = create_parsed_res(res, cmd);
	if (last_command_rv(res, parsed_res))
		return (parsed_res);
	while (res[++i])
	{
		if (ft_strcmp(res[i], "$?") == 0)
			parsed_res[j] = rv_itoa(cmd->cmd_rv);
		else if ((strings_to_join(res, i)) > 0)
			parsed_res[j] = expander(ft_strjoin(res[i],
						res[++i]), var_env, res, cmd);
		else
			parsed_res[j] = expander(res[i], var_env, res, cmd);
		parsed_res[j] = parsed_res_error(parsed_res, j, cmd);
		parsed_res[j] = remove_antislashes(parsed_res[j], res[i], var_env, cmd);
		j++;
	}
	parsed_res[j] = NULL;
	return (parsed_res);
}
