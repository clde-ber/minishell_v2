/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:21:33 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/23 08:49:03 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*export_errors(char *str_first, char *str_secd, int quotes,
char *res)
{
	char *operator;
	char *str_f;
	char *str_s;

	str_f = ft_strtrim(str_first, "\'");
	str_s = ft_strtrim(str_secd, "\'");
	operator = find_op(res);
	write(1, "bash: export: '", 16);
	if (quotes % 2 == 0)
		write(1, str_f, ft_strlen(str_f));
	else
		write(1, str_first, ft_strlen(str_first));
	write(1, operator, ft_strlen(operator));
	if (quotes == 1 || quotes == 4)
		write(1, str_s, ft_strlen(str_s));
	else
		write(1, str_secd, ft_strlen(str_secd));
	write(1, "': not a valid identifier\n", 26);
	free(str_first);
	free(str_secd);
	free(str_f);
	free(str_s);
	return (NULL);
}

char		*valid_export(char *str_first, char *str_secd, int quotes,
char *res)
{
	char *operator;
	char *str_f;
	char *str_s;

	str_f = ft_strdup(str_first);
	str_s = ft_strdup(str_secd);
	operator = find_op(res);
	if (quotes % 2 == 0)
	{
		free(str_f);
		str_f = ft_strtrim(str_first, "\'");
		free(str_first);
	}
	if (quotes == 1 || quotes == 4)
	{
		free(str_s);
		str_s = ft_strtrim(str_secd, "\'");
		free(str_secd);
	}
	return (ft_strjoin_free(join_a_free(str_f, operator), str_s));
}

void		env_quotes_a_values(char **str_first, char **str_secd,
int *quotes)
{
	char *str_f;
	char *str_s;

	str_f = ft_strtrim(*str_first, "\"");
	str_s = ft_strtrim(*str_secd, "\"");
	if (ft_strlen(*str_first) != ft_strlen(str_f) &&
	ft_strlen(*str_secd) == ft_strlen(str_s))
		*quotes = 1;
	if (ft_strlen(*str_secd) != ft_strlen(str_s) &&
	ft_strlen(*str_first) == ft_strlen(str_f))
		*quotes = 2;
	if (ft_strlen(*str_first) != ft_strlen(str_f) &&
	ft_strlen(*str_secd) != ft_strlen(str_s))
		*quotes = 3;
	if (ft_strlen(*str_first) == ft_strlen(str_f) &&
	ft_strlen(*str_secd) == ft_strlen(str_s))
		*quotes = 4;
	free(*str_first);
	free(*str_secd);
	*str_first = str_f;
	*str_secd = str_s;
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
	if (even_or_odd(*str_first) % 2 == 0 || even_or_odd(*str_first) == 0)
		*str_first = replace_by_env(*str_first, var_env, cmd, 0);
	cmd->index = 0;
	if (even_or_odd(*str_secd) % 2 == 0 || even_or_odd(*str_secd) == 0)
		*str_secd = replace_by_env_value(*str_secd, var_env, cmd);
}
