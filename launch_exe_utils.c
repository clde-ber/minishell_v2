/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exe_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:50 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/27 18:07:59 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Functions that support launch_exe ones. Output the directories path and the
** name of the file. Creates two dimensional arrays for execve to perform which
** are environment and argument related.
*/

char	*ft_get_filename(const char *s, int c)
{
	char	*str;
	int		i;

	str = (char *)s;
	i = ft_strlen(str);
	while (i)
	{
		if (str[i] == c)
			return (ft_strdup((const char *)&str[i + 1]));
		i--;
	}
	return (NULL);
}

char	*get_path(char *path, char c)
{
	char	*str;
	int		i;
	int		j;

	j = 1;
	str = ft_strdup((char *)path);
	i = ft_strlen(str);
	while (i)
	{
		if (str[i] == c)
		{
			while (str[i + j])
			{
				str[i + j] = '\0';
				j++;
			}
			return (str);
		}
		i--;
	}
	return (NULL);
}

char	**arg_tab(char *exe, char *path, char **env)
{
	char	**ret;

	if (!(ret = malloc(sizeof(char *) * 3)))
		return (0);
	ret[0] = ft_strdup(path);
	ret[1] = ft_strdup((char *)env);
	ret[2] = NULL;
	return (ret);
}

char	**env_tab(char *path)
{
	char	**ret;

	if (!(ret = malloc(sizeof(char *) * 3)))
		return (0);
	ret[0] = ft_strjoin("HOME=", ".");
	ret[1] = ft_strjoin("PATH=", path);
	ret[2] = NULL;
	return (ret);
}
