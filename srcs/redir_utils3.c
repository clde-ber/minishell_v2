/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 11:17:25 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/10 10:49:13 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**failed_fd(t_fd *f, char **res)
{
	restore_fds(f);
	if (handle_fds(res) == -1)
		ft_putstr_fd("Error: file cannot be opened\n", 2);
	else
		ft_putstr_fd("Error: no specified file\n", 2);
	return (ft_calloc(sizeof(char *), 2));
}

int	get_k(int k, char **res, int i, int j)
{
	if (count_pipes(res) == i)
		k = count_tabs(res);
	else
	{
		k = j;
		while (ft_strcmp(res[k], "|") != 0)
			k++;
	}
	return (k);
}

char	**middle_pipe(char **res, int i)
{
	int		j;
	int		k;
	char	**tabl;

	j = 0;
	k = 0;
	while (k != i)
	{
		if (ft_strcmp(res[j], "|") == 0)
			k++;
		j++;
	}
	k = get_k(k, res, i, j);
	tabl = malloc(sizeof(char *) * ((k - j) + 1));
	if (!tabl)
		return (NULL);
	i = 0;
	while (i < ((k - j)))
	{
		tabl[i] = ft_strdup(res[j + i]);
		i++;
	}
	tabl[i] = NULL;
	return (tabl);
}

char	**end_redir(char **res, t_fd *f)
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
		tabl = end_redir(buf, f);
		free_tabtab(buf);
		if (tabl == NULL)
			return (NULL);
	}
	return (tabl);
}

int	end_pipe(t_fd *f, t_mp *mp)
{
	close(mp->fd[0]);
	close(mp->fd[1]);
	free_tabtab(mp->first);
	free_tabtab(f->save_pipe);
	return (0);
}
