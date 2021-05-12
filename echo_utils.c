/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 21:57:53 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/02 18:11:10 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*echo_option(char *output, int option)
{
	char	*buf;

	if (option == 0 && output != NULL)
	{
		buf = ft_strdup(output);
		free(output);
		output = ft_strjoin(buf, "\n");
		free(buf);
	}
	if (output == NULL)
	{
		if (option == 0)
			output = ft_strdup("\n");
		else
			output = ft_strdup("");
	}
	return (output);
}

void	go_trim(char **res, int i, int c)
{
	char	*buf;

	if (c == 0)
	{
		buf = ft_strtrim(res[i], "\"");
		free(res[i]);
		res[i] = ft_strdup(buf);
		free(buf);
	}
	else if (c == 1)
	{
		buf = ft_strtrim(res[i], "\'");
		free(res[i]);
		res[i] = ft_strdup(buf);
		free(buf);
	}
}

char	*get_word(char **res, int i, int j)
{
	char	*str;
	int		t;
	int		k;

	t = 0;
	j++;
	k = j;
	while (ft_isspace(res[i][j]) == 0 && res[i][j] && res[i][j] != '\"')
	{
		t++;
		j++;
	}
	if (!(str = malloc(sizeof(char) * t + 1)))
		return (NULL);
	t = 0;
	while (ft_isspace(res[i][k]) == 0 && res[i][k] && res[i][k] != '\"')
		str[t++] = res[i][k++];
	return (str);
}
