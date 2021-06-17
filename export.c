/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:35:29 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/17 08:44:05 by clde-ber         ###   ########.fr       */
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
	ft_putstr_fd("bash: export: '", 2);
	if (quotes % 2 == 0)
		ft_putstr_fd(str_f, 2);
	else
		ft_putstr_fd(str_first, 2);
	ft_putstr_fd(operator, 2);
	if (quotes == 1 || quotes == 4)
		ft_putstr_fd(str_s, 2);
	else
		ft_putstr_fd(str_secd, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
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
