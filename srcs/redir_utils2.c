/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:17:22 by budal-bi          #+#    #+#             */
/*   Updated: 2021/06/17 15:06:41 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**failed_fd(t_fd *f, char **res)
{
	restore_fds(f);
	if (handle_fds(res, f) == -1)
		ft_putstr_fd("Error: file cannot be opened\n", 2);
	else
		ft_putstr_fd("Error: no specified file\n", 2);
	return (ft_calloc(sizeof(char *), 2));
}

int	check_valid_res_bis(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "|") == 0 || ft_strcmp(str[i], "<") == 0 ||
		ft_strcmp(str[i], ">") == 0 || ft_strcmp(str[i], ">>") == 0)
		{
			if (!str[i + 1])
				return (1);
			else if (ft_strcmp(str[i + 1], "|") == 0 || ft_strcmp(str[i + 1],
			"<") == 0 || ft_strcmp(str[i + 1], ">") == 0 || ft_strcmp(str[i + 1]
			, ">>") == 0)
				return (1);
		}
		i++;
	}
	return (0);
}

int	check_valid_res(char **str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (check_valid_res_bis(str))
		return (1);
	while (str[i])
	{
		if (ft_is_fail_char(str[i]))
			j++;
		i++;
	}
	if (j == i)
		return (1);
	else
		return (0);
}

char	**divide_pipe(t_fd *f)
{
	int		m;
	int		i;
	char	**tabl;

	i = 0;
	m = count_tabs(f->res) - chrtabtab(f->res, "|");
	if (!(f->save_pipe = malloc(sizeof(char *) * (m + 2))))
		return (NULL);
	if (!(tabl = malloc(sizeof(char *) * (chrtabtab(f->res, "|") + 2))))
		return (NULL);
	while (i < chrtabtab(f->res, "|"))
	{
		tabl[i] = ft_strdup(f->res[i]);
		i++;
	}
	tabl[i] = NULL;
	i = 0;
	while (f->res[chrtabtab(f->res, "|") + i + 1])
	{
		f->save_pipe[i] = ft_strdup(f->res[chrtabtab(f->res, "|") + i + 1]);
		i++;
	}
	f->save_pipe[i] = NULL;
	return (tabl);
}