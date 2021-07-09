/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:35:29 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/08 16:31:27 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

char	*export_errors(char *str_first, char *str_secd, char *res)
{
	ft_putstr_fd("bash: export: '", 2);
	ft_putstr_fd(res, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	ft_free_2_strings(str_first, str_secd);
	return (res);
}

void	ft_free_2_strings(char *s1, char *s2)
{
	free_string(s1);
	free_string(s2);
}

char	*valid_export(char *str_first, char *str_secd, char *res)
{
	ft_free_2_strings(str_first, str_secd);
	return (res);
}
