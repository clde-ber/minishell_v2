/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/05 14:21:33 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/14 16:12:38 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_export_errors(char *s1, char *s2, char *s3, char *s4)
{
	free_string(s1);
	free_string(s2);
	free_string(s3);
	free_string(s4);
}

void	if_s_quotes(char *str_first, char *str_secd, char **str_f,
char **str_s)
{
	if (str_first[0] == '\'')
		*str_f = ft_strtrim(str_first, "\'");
	else
		*str_f = ft_strdup(str_first);
	if (str_secd[0] == '\'')
		*str_s = ft_strtrim(str_secd, "\'");
	else
		*str_s = ft_strdup(str_secd);
}

char	*export_errors(char *str_first, char *str_secd, int quotes,
char *res)
{
	char	*operator;
	char	*str_f;
	char	*str_s;

	if_s_quotes(str_first, str_secd, &str_f, &str_s);
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
	free_export_errors(str_first, str_secd, str_f, str_s);
	return (ft_strdup(""));
}

void	ft_free_2_strings(char *s1, char *s2)
{
	free_string(s1);
	free_string(s2);
}

char	*valid_export(char *str_first, char *str_secd, int quotes,
char *res)
{
	char	*operator;
	char	*str_f;
	char	*str_s;

	str_f = ft_strdup(str_first);
	str_s = ft_strdup(str_secd);
	operator = find_op(res);
	if (quotes % 2 == 0)
	{
		if (str_first[0] == '\'')
		{
			free(str_f);
			str_f = ft_strtrim(str_first, "\'");
		}
	}
	if (quotes == 1 || quotes == 4)
	{
		if (str_secd[0] == '\'')
		{
			free(str_s);
			str_s = ft_strtrim(str_secd, "\'");
		}
	}
	ft_free_2_strings(str_first, str_secd);
	return (ft_strjoin_free(join_a_free(str_f, operator), str_s));
}

void	if_d_quotes(char *str_first, char *str_secd, char **str_f, char **str_s)
{
	if (str_first[0] == '\"')
		*str_f = ft_strtrim(str_first, "\"");
	else
		*str_f = ft_strdup(str_first);
	if (str_secd[0] == '\"')
		*str_s = ft_strtrim(str_secd, "\"");
	else
		*str_s = ft_strdup(str_secd);
}

void	env_quotes_a_values(char **str_first, char **str_secd,
int *quotes, char **name)
{
	char	*str_f;
	char	*str_s;

	if_d_quotes(*str_first, *str_secd, &str_f, &str_s);
	if (ft_strlen(*str_first) != ft_strlen(str_f)
		&& ft_strlen(*str_secd) == ft_strlen(str_s))
		*quotes = 1;
	if (ft_strlen(*str_secd) != ft_strlen(str_s)
		&& ft_strlen(*str_first) == ft_strlen(str_f))
		*quotes = 2;
	if (ft_strlen(*str_first) != ft_strlen(str_f)
		&& ft_strlen(*str_secd) != ft_strlen(str_s))
		*quotes = 3;
	if (ft_strlen(*str_first) == ft_strlen(str_f)
		&& ft_strlen(*str_secd) == ft_strlen(str_s))
		*quotes = 4;
	ft_free_2_strings(*str_first, *str_secd);
	*str_first = str_f;
	*str_secd = str_s;
	*name = get_env_name(*quotes, *str_first);
	if (!(*name))
		(*str_first)[0] = '\0';
}

void	which_is_name_a_value(char **str_first, char **str_secd, char **p_bin, char *res)
{
	if (res[0] == '=')
		{
			*str_first = ft_strdup("");
			*str_secd = ft_strdup(p_bin[0]);
		}
		else
		{
			*str_first = ft_strdup(p_bin[0]);
			*str_secd = ft_strdup("");
		}
}

void	split_env_name_a_value(char **str_first, char **str_secd,
char **p_bin, char *res)
{
	char	*str_f;
	char	*str_s;

	str_f = NULL;
	str_s = NULL;
	if (p_bin && p_bin[0] && p_bin[1])
	{
		*str_first = ft_strdup(p_bin[0]);
		if (p_bin[1])
			*str_secd = ft_strdup(p_bin[1]);
		else
			*str_secd = ft_strdup("");
	}
	else if (p_bin && p_bin[0])
		which_is_name_a_value(str_first, str_secd, p_bin, res);
	else
	{
		*str_first = ft_strdup(res);
		*str_secd = ft_strdup("");
	}
}

void	export_replace_by_env_value(char **str_first, char **str_secd,
t_list *var_env, t_command *cmd)
{
	cmd->index = 0;
	if (even_or_odd(*str_first) % 2 == 0 || even_or_odd(*str_first) == 0)
		*str_first = replace_by_env_value(*str_first, var_env, cmd);
	cmd->index = 0;
	if (even_or_odd(*str_secd) % 2 == 0 || even_or_odd(*str_secd) == 0)
		*str_secd = replace_by_env_value(*str_secd, var_env, cmd);
}
