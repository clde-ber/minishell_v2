/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:47:58 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/10 15:50:24 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_mp(t_mp *mp, t_fd *f)
{
	mp->first = divide_pipe(f);
	pipe(mp->fd);
	mp->pid = fork();
	g_sig.boolean = 2;
}

void	fd_multipipe(int j, int i, t_test *t, int k)
{
	if (k == 0)
	{
		if (j != i)
			dup2(t->pipes[1], 1);
		if (j != 0)
			dup2(t->prec->pipes[0], 0);
	}
	else
	{
		close(t->pipes[1]);
		if (j == i)
			close(t->pipes[0]);
		if (j != 0)
			close(t->prec->pipes[0]);
	}
}

int	exec_pipe(t_test *t, int j, t_mult *mul, int i)
{
	t_mp	mp[1];
	int		ret;

	ret = EXIT_FAILURE;
	if (pipe(t->pipes))
		return (-1);
	mp->pid = fork();
	if (mp->pid < 0)
		return (-1);
	else if (mp->pid == 0)
	{
		fd_multipipe(j, i, t, 0);
		go_instruction(end_redir(t->res, *mul->f), mul->var_e, *mul->cmd, \
			*mul->env);
		exit(mp->status);
	}
	else
	{
		if (WIFSIGNALED(mp->status) && g_sig.boolean != -1)
			g_sig.boolean++;
		waitpid(mp->pid, &mp->status, 0);
		fd_multipipe(j, i, t, 1);
	}
	return (ret);
}

int	handle_multipipes(t_fd *f, t_list *var_env, t_command *cmd, char **env)
{
	int		j;
	t_test	*t;
	t_test	**start;
	t_mult	mul[1];
	int		ret;

	mul->cmd = &cmd;
	init_mul(mul, var_env, f, env);
	j = 0;
	start = NULL;
	t = ft_lstnew2(middle_pipe(f->res, j));
	start = &t;
	set_list_mp(start, f);
	while (j <= count_pipes(f->res))
	{
		ret = exec_pipe(t, j, mul, count_pipes(f->res));
		free_tabtab(t->res);
		if (t->next != NULL)
			t = t->next;
		j++;
	}
	destroy_list(start, t);
	return (ret);
}
