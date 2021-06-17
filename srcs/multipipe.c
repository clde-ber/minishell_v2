/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:47:58 by budal-bi          #+#    #+#             */
/*   Updated: 2021/06/17 15:06:41 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_k(int k, char **res, int i, int j)
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
	if (!(tabl = malloc(sizeof(char *) * ((k - j) + 1))))
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

void	print_tabtab(char **res)
{
	int		i;

	i = 0;
	while (res[i])
	{
		ft_putstr_fd(res[i], 2);
		i++;
	}
}

int		handle_multipipes(t_fd *f, t_list *var_env, t_command *cmd,
char **env)
{
	t_mp mp[1];

	mp->count = 0;
	mp->fdd = 0;
	mp->pid = 0;
	while (mp->count < count_pipes(f->res) + 1)
	{
		pipe(mp->fd);
		if ((mp->pid = fork()) == -1)
			exit(1);
		else if (mp->pid == 0)
		{
			dup2(mp->fdd, 0);
			if (mp->count < count_pipes(f->res))
				dup2(mp->fd[1], 1);
			close(mp->fd[0]);
			go_instruction(end_redir(middle_pipe(f->res, mp->count), f),
			var_env, cmd, env);
			exit(mp->status);
		}
		waitpid(-1, &mp->status, 0);
		close(mp->fd[1]);
		mp->fdd = mp->fd[0];
		mp->count++;
	}
}
