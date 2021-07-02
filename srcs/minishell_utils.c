/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:57:35 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**Useful functions created for minishell
**check word and search word detect keywords in commands
**Check whether the recreated builtins have to be called vs execve
*/

#include "../includes/minishell.h"

int	is_handled_cmd(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	if (ft_strcmp(str, "cd") == 0)
		return (1);
	if (ft_strcmp(str, "pwd") == 0)
		return (1);
	if (ft_strcmp(str, "export") == 0)
		return (1);
	if (ft_strcmp(str, "unset") == 0)
		return (1);
	if (ft_strcmp(str, "env") == 0)
		return (1);
	if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

int	ft_strchr_bis(const char *s, int c)
{
	char	to_find;
	int		i;

	i = 0;
	to_find = c;
	while (s[i])
	{
		if (s[i] == to_find)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' \
	|| c == ' ')
		return (1);
	return (0);
}

int	check_word(char *str, char *to_find, int i)
{
	int		j;

	j = 0;
	while (to_find[j])
	{
		if (str[i + j] == to_find[j])
			j++;
		else
			return (0);
	}
	return (1);
}

int	search_word(char *str, char *to_find)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == to_find[0])
		{
			if (check_word(str, to_find, i) == 1)
				return (1);
		}
		i++;
	}
	return (0);
}
