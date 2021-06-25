/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:47:58 by budal-bi          #+#    #+#             */
/*   Updated: 2021/06/25 12:41:41 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	init_mp(t_mp *mp, int i, t_fd *f)
{
	if (i == 0)
	{
		mp->count = 0;
		mp->fdd = 0;
		mp->pid = 0;
	}
	else
	{
		mp->first = divide_pipe(f);
		pipe(mp->fd);
		mp->pid = fork();
	}
	g_sig.boolean = 2;
}

void	prep_fds(t_mp *mp, t_fd *f)
{
	dup2(mp->fdd, 0);
	if (mp->count < count_pipes(f->res))
		dup2(mp->fd[1], 1);
	close(mp->fd[0]);
}

void	parent_process_mult(t_mp *mp, int count)
{
	close(mp->fd[1]);
	mp->fdd = mp->fd[0];
	mp->count++;
	if (mp->count == count)
	{
		while (wait(NULL) >= 0)
			;
	}
}

int	handle_multipipes(t_fd *f, t_list *var_env, t_command *cmd, char **env)
{
	t_mp	mp[1];

	init_mp(mp, 0, f);
	while (mp->count < count_pipes(f->res) + 1)
	{
		pipe(mp->fd);
		mp->pid = fork();
		if (mp->pid == -1)
			return (0);
		else if (mp->pid == 0)
		{
			prep_fds(mp, f);
			go_instruction(end_redir(middle_pipe(f->res, mp->count), f),
				var_env, cmd, env);
			exit(mp->status);
		}
		else
		{
			if (WIFSIGNALED(mp->status) && g_sig.boolean != -1)
				g_sig.boolean++;
			waitpid(mp->pid, &mp->status, 1);
			parent_process_mult(mp, count_pipes(f->res) + 1);
		}
	}
	return (0);
}
