/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:21 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/08 08:53:38 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Functions that help re-parsing all command line arguments. Output environment
** linked list names and values to be compared, check whether the syntax
** of an environment variable is correct and output strings without antislashes.
*/

char		*search_env_name(char *str, t_list *var_env)
{
	int		chg;
	char	*ret;

	chg = -1;
	while (var_env && chg == -1)
	{
		if (ft_strcmp(var_env->name, str) == 0)
		{
			ret = ft_strdup(var_env->name);
			return (ret);
		}
		var_env = var_env->next;
	}
	return (NULL);
}

char		*search_env_value(char *str, t_list *var_env)
{
	char	*ret;

	ret = NULL;
	while (var_env->next)
	{
		if (ft_strcmp(var_env->name, str) == 0)
		{
			ret = ft_strdup(var_env->value);
			return (ret);
		}
		var_env = var_env->next;
	}
	if (ft_strcmp(var_env->name, str) == 0)
	{
		ret = ft_strdup(var_env->value);
		return (ret);
	}
	return (ft_strdup(""));
}

char    *antislashes_dolls(char *str)
{
    int i;
    int j;
    char *tmp;

    i = 0;
    j = 0;
    if (!(tmp = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (0);
    while (str[i])
    {
        if (str[i] == '\\' && str[i + 1] == '$')
            i++;
		else
        {	
			tmp[j] = str[i];
        	i++;
        	j++;
		}
    }
    tmp[j] = '\0';
	free(str);
    return (tmp);
}

char		*antislashes_a_quotes(char *str)
{
	char	*ret;
	int		len;
	int		i;
	int		j;

	len = (int)ft_strlen(str);
	if (len > 2 && str[len - 2] == '\\' && str[len - 3] == '\\')
		len = len - 2;
	i = 0;
	j = 0;
	if (!(ret = malloc(sizeof(char) * (len + 1))))
		return (0);
	while (i < len)
	{
		if (i < len && (((i == 0 && str[i] == '\"') || ((i && str[i - 1] != '\\' && str[i] == '\"')))) && (str[i + 1] != '\"'))
		{
			ret[j] = str[i];
			i++;
			j++;
			while (i < len && (str[i] != '\"' || (str[i] == '\"' && str[i - 1] == '\\')))
			{
				if (!(str[i - 1] == '\\' && str[i] == '\\'))
				{
					ret[j] = str[i];
					j++;
				}
				i++;
			}
		}
		else if (i < len && (((i == 0 && str[i] == '\'') || ((i && str[i - 1] != '\\' && str[i] == '\'')))) && (str[i + 1] != '\''))
		{
			ret[j] = str[i];
			i++;
			j++;
			while (i < len && (str[i] != '\'' || (str[i] == '\'' && str[i - 1] == '\\')))
			{
				if (!(str[i - 1] == '\\' && str[i] == '\\'))
				{
					ret[j] = str[i];
					j++;
				}
				i++;
			}
		}
	/*	else if (i < len && str[i] == '\\' && str[i + 1] && str[i + 1] != '$' && str[i + 1]
		!= '\\')
			i++;*/
		else if (i < len)
		{
			ret[j] = str[i];
			j++;
			i++;
		}
	}
	ret[j] = '\0';
	free(str);
	str = NULL;
	return (ret);
}

int			is_valid_env_c(char c)
{
	if (ft_isalnum(c) || c == '_' || c == '\t' || c == '\n'
	|| c == '\r' || c == '\v' || c == '\f' || c == ' ' ||
	c == '+' || c == '\'')
		return (1);
	return (0);
}

char		*get_env_name(int quotes, char *str_first)
{
	char *name;

	name = NULL;
	if (quotes % 2 == 0)
		name = ft_strtrim(str_first, "\'");
	else
		name = ft_strdup(str_first);
	if (ft_strlen(name) && name[ft_strlen(name) - 1] == '+')
		name[ft_strlen(name) - 1] = '\0';
	return (name);
}