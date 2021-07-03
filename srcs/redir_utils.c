/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 19:01:15 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/03 12:25:24 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	open_fds_out(char **res, int i, int m)
{
	int		fd;

	if (!res[i + 1])
		return (-2);
	i++;
	close(1);
	if (m == 0)
		fd = open(res[i], O_CREAT | O_RDWR | O_TRUNC, 0777);
	else
	{
		fd = open(res[i], O_APPEND | O_RDWR, 0777);
		if (fd == -1)
			fd = open(res[i], O_CREAT | O_RDWR | O_TRUNC, 0777);
	}
	return (fd);
}

int	open_fds_in(char **res, int i)
{
	int		fd;

	if (!res[i + 1])
		return (-2);
	i++;
	close(0);
	fd = open(res[i], O_RDONLY, 0777);
	return (fd);
}

int	handle_fds(char **res)
{
	int		i;

	i = 0;
	while (res[i])
	{
		if (ft_strcmp(res[i], ">") == 0)
			return (open_fds_out(res, i, 0));
		else if (ft_strcmp(res[i], ">>") == 0)
			return (open_fds_out(res, i, 1));
		else if (ft_strcmp(res[i], "<") == 0)
			return (open_fds_in(res, i));
		i++;
	}
	return (-127);
}

char	**get_redir_ready(char **res)
{
	int		j;
	char	**tabl;

	j = 0;
	if (count_tabs(res) == 2)
		return (NULL);
	tabl = malloc(sizeof(char *) * (count_tabs(res) - 1));
	if (!tabl)
		return (NULL);
	while (res[j] && ft_strcmp(res[j], "<") != 0 && ft_strcmp(res[j], ">") != 0
		&& ft_strcmp(res[j], ">>") != 0)
	{
		tabl[j] = ft_strdup(res[j]);
		j++;
	}
	j += 2;
	while (res[j])
	{
		tabl[j - 2] = ft_strdup(res[j]);
		j++;
	}
	tabl[j - 2] = NULL;
	return (tabl);
}

char	**end_redir_pipe(char **res, t_fd *f)
{
	char	**tabl;
	char	**buf;

	if (chrtabtab(res, ">") == -1 && chrtabtab(res, ">>") == -1 && \
		chrtabtab(res, "<") == -1)
		return (res);
	if (handle_fds(res) < 0)
		return (failed_fd(f, res));
	tabl = get_redir_ready(res);
	while (chrtabtab(tabl, ">") != -1 || chrtabtab(tabl, ">>") != -1 || \
		chrtabtab(tabl, "<") != -1)
	{
		buf = copy_tabtab(tabl);
		free_tabtab(tabl);
		tabl = end_redir_pipe(buf, f);
		free_tabtab(buf);
		if (tabl == NULL)
			return (NULL);
	}
	free_tabtab(res);
	return (tabl);
}
