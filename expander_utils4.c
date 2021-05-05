/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:21:33 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/05 15:53:38 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*export_errors(char *str_first, char *str_secd, int quotes,
char *res)
{
	char *operator;

	operator = find_op(res);
	write(1, "bash: export: '", 16);
	if (quotes % 2 == 0)
		write(1, ft_strtrim(str_first, "\'"), ft_strlen(ft_strtrim(str_first,
		"\'")));
	else
		write(1, str_first, ft_strlen(str_first));
	write(1, operator, ft_strlen(operator));
	if (quotes == 1 || quotes == 4)
		write(1, ft_strtrim(str_secd, "\'"), ft_strlen(ft_strtrim(str_secd,
		"\'")));
	else
		write(1, str_secd, ft_strlen(str_secd));
	write(1, "': not a valid identifier\n", 26);
	return (NULL);
}

char		*valid_export(char *str_first, char *str_secd, int quotes,
char *res)
{
	char *operator;

	operator = find_op(res);
	if (quotes % 2 == 0)
		str_first = ft_strtrim(str_first, "\'");
	if (quotes == 1 || quotes == 4)
		str_secd = ft_strtrim(str_secd, "\'");
	return (ft_strjoin_free(join_a_free(str_first, operator), str_secd));
}

void		env_quotes_a_values(char **str_first, char **str_secd,
int *quotes)
{
	if (ft_strlen(*str_first) != ft_strlen(ft_strtrim(*str_first, "\"")) &&
	ft_strlen(*str_secd) == ft_strlen(ft_strtrim(*str_secd, "\"")))
		*quotes = 1;
	if (ft_strlen(*str_secd) != ft_strlen(ft_strtrim(*str_secd, "\"")) &&
	ft_strlen(*str_first) == ft_strlen(ft_strtrim(*str_first, "\"")))
		*quotes = 2;
	if (ft_strlen(*str_first) != ft_strlen(ft_strtrim(*str_first, "\"")) &&
	ft_strlen(*str_secd) != ft_strlen(ft_strtrim(*str_secd, "\"")))
		*quotes = 3;
	if (ft_strlen(*str_first) == ft_strlen(ft_strtrim(*str_first, "\"")) &&
	ft_strlen(*str_secd) == ft_strlen(ft_strtrim(*str_secd, "\"")))
		*quotes = 4;
	*str_first = ft_strtrim(*str_first, "\"");
	*str_secd = ft_strtrim(*str_secd, "\"");
}

void		split_env_name_a_value(char **str_first, char **str_secd,
char **p_bin, char *res)
{
	if (ft_strchr(res, '='))
	{
		*str_first = ft_strdup(p_bin[0]);
		*str_secd = ft_strdup(&ft_strchr(res, '=')[1]);
	}
	else
	{
		*str_first = ft_strdup(res);
		*str_secd = ft_strdup("");
	}
}

void		export_replace_by_env_value(char **str_first, char **str_secd,
t_list *var_env, t_command *cmd)
{
	cmd->index = 0;
	if (*str_first[0] != '\'')
		*str_first = replace_by_env(*str_first, var_env, cmd, 0);
	cmd->index = 0;
	if (*str_secd[0] != '\'')
		*str_secd = replace_by_env_value(*str_secd, var_env, cmd);
}
