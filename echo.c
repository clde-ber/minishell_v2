/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:13:10 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/20 19:29:05 by budal-bi         ###   ########.fr       */
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

char	*get_echo_output(char *output, char **res, int i)
{
	if (output == NULL)
		output = ft_strdup(res[i]);
	else
	{
		output = ft_strjoin_free(output, ft_strdup(" "));
		output = ft_strjoin_free(output, ft_strdup(res[i]));
	}
}

void	ft_echo(char **res, t_list *var_env)
{
	int		option;
	int		i;
	char	*output;

	i = 1;
	output = NULL;
	option = 0;
	if (res[i] && ft_strcmp(res[i], "-n") == 0)
	{
		option = 1;
		i++;
	}
	while (res[i])
	{
		output = get_echo_output(output, res, i);
		i++;
	}
	output = echo_option(output, option);
	ft_putstr_fd(output, 1);
	free(output);
}
