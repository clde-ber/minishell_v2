/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe_ok.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:47:58 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/09 13:14:15 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	end_multipipe(t_mp *mp)
{
	close(mp->fd[0]);
	close(mp->fd[1]);
	close(mp->fdd);
	return (0);
}

// int	handle_multipipes(t_fd *f, t_list *var_env, t_command *cmd, char **env)
// {
// 	t_mp	mp[1];
// 	int i;

// 	i = 0;
// 	init_mp(mp, 0, f);
// 	mp->count = count_pipes(f->res);
// 	pipe(mp->fd);
// 	// close(mp->fd[0]);
// 	dup2(mp->fd[1], 1);
// 	go_instruction(end_redir(middle_pipe(f->res, i), f), var_env, cmd, env);
// 	dup2(mp->fd[0], 0);
// 	ft_putstr_fd("ok", 2);
// 	i++;
// 	while (mp->count != count_pipes(f->res) - 1)
// 	{
// 		mp->pid = fork();
// 		if (mp->pid == -1)
// 			return (0);
// 		else if (mp->pid == 0)
// 		{
// 			ft_putstr_fd("ok", 2);
// 			ft_putstr_nbr(i, 2);
// 			go_instruction(end_redir(middle_pipe(f->res, i), f), var_env, cmd, env);
// 			exit(mp->status);
// 		}
// 		else
// 		{
// 			// if (WIFSIGNALED(mp->status) && g_sig.boolean != -1)
// 			// 	g_sig.boolean++;
// 			waitpid(mp->pid, &mp->status, 1);
// 			// waitpid(mp->pid, &mp->status, 0);
// 			if (mp->count == count_pipes(f->res) - 2)
// 				close(mp->fd[1]);
// 			ft_putstr_fd("ok", 2);
// 		}
// 		mp->count--;
// 		i++;
// 	}
// 	waitpid(mp->pid, &mp->status, 1);
// 	ft_putstr_fd("ping", 4);
// 	ft_putstr_nbr(i, 2);
// 	close(mp->fd[1]);
// 	dup2(1, f->save_out);
// 	go_instruction(end_redir(middle_pipe(f->res, i), f), var_env, cmd, env);
// 	ft_putstr_fd("done", 2);
// 	close(mp->fd[0]);
// 	// while (wait(NULL) >= 0)
// 	// 	;
// 	return (0);
// }

// void	prep_fds(t_mp *mp, t_fd *f, int *test)
// {
// 	if (mp->count == 0)
// 	{
// 		close(mp->fd[0]);
// 		dup2(mp->fd[1], 1);
// 	}
// 	else if (mp->count == count_pipes(f->res) + 1)
// 	{
// 		if (mp->count % 2 == 1)
// 			dup2(mp->fd[0], 0);
// 		else
// 			dup2(test[0], 0);
// 	}
// 	else
// 	{
// 		if (mp->count % 2 == 1)
// 		{
// 			dup2(mp->fd[0], 0);
// 			dup2(test[1], 1);
// 			close(test[0]);
// 			close(mp->fd[1]);
// 		}
// 		else
// 		{
// 			dup2(mp->fd[1], 1);
// 			dup2(test[0], 0);
// 			close(mp->fd[0]);
// 			close(test[1]);
// 		}
// 	}
// }

// void	parent_process_mult(t_mp *mp, int count, t_fd *f, int *test)
// {
// 	if (mp->count == 0)
// 		close(mp->fd[1]);
// 	else if (mp->count == count_pipes(f->res) + 1)
// 	{
// 		if (mp->count % 2 == 1)
// 			close(mp->fd[0]);
// 		else
// 			close(test[0]);
// 	}
// 	else
// 	{
// 		if (mp->count % 2 == 1)
// 		{
// 			close(mp->fd[0]);
// 			close(test[1]);
// 		}
// 		else
// 		{
// 			close(mp->fd[1]);
// 			close(test[0]);
// 		}
// 	}
// 	// mp->fdd = mp->fd[0];
// 	mp->count++;
// 	if (mp->count == count)
// 	{
// 		while (wait(NULL) >= 0)
// 			;
// 	}
// }

// int	handle_multipipes(t_fd *f, t_list *var_env, t_command *cmd, char **env)
// {
// 	t_mp	mp[1];
// 	int test[2];

// 	init_mp(mp, 0, f);
// 	pipe(mp->fd);
// 	pipe(test);
// 	mp->fdd = mp->fd[0];
// 	while (mp->count <= count_pipes(f->res) + 1)
// 	{
// 		mp->pid = fork();
// 		if (mp->pid == -1)
// 			return (0);
// 		else if (mp->pid == 0)
// 		{
// 			prep_fds(mp, f, test);
// 			go_instruction(end_redir(middle_pipe(f->res, mp->count), f),
// 				var_env, cmd, env);
// 			exit(mp->status);
// 		}
// 		else
// 		{
// 			if (WIFSIGNALED(mp->status) && g_sig.boolean != -1)
// 				g_sig.boolean++;
// 			waitpid(mp->pid, &mp->status, 1);
// 			parent_process_mult(mp, count_pipes(f->res) + 1, f, test);
// 		}
// 	}
// 	return (0);
// }


// void	prep_fds(t_mp *mp, t_fd *f, int *test)
// {
// 	ft_putstr_fd("ok", 2);
// 	ft_putstr_nbr(mp->count, 2);
// 	// int i = 0;
// 	if (mp->count == 0)
// 	{
// 		close(test[0]);
// 		dup2(test[1], 1);
// 		// ft_putstr_nbr(1, 2);
// 		// i = 2;
// 		// while (i <= count_pipes(f->res) * 2)
// 		// {
// 		// 	close(test[i]);
// 		// 	i++;
// 		// }
// 	}
// 	else if (mp->count == count_pipes(f->res))
// 	{
// 		dup2(test[(mp->count -1) * 2], 0);
// 		dup2(1, f->save_out);
// 		// ft_putstr_nbr((mp->count -1) * 2, 2);
// 		// while (i <= count_pipes(f->res) * 2)
// 		// {
// 		// 	if (i != (mp->count - 1) * 2)
// 		// 		close(test[i]);
// 		// 	i++;
// 		// }
// 	}
// 	else
// 	{
// 		dup2(test[(mp->count - 1) * 2], 0);
// 		// ft_putstr_nbr((mp->count -1) * 2, 2);
// 		dup2(test[((mp->count - 1) * 2) + 3], 1);
// 		// ft_putstr_nbr(((mp->count - 1) * 2) + 3, 2);
// 		// while (i <= count_pipes(f->res) * 2)
// 		// {
// 		// 	if (i != (mp->count - 1) * 2 && i != ((mp->count - 1) * 2) + 3)
// 		// 		close(test[i]);
// 		// 	i++;
// 		// }
// 		// close(test[((mp->count - 1) * 2) + 1]);
// 		// close(test[((mp->count - 1) * 2) + 2]);
// 	}
// }

// void	close_fds(t_mp *mp, t_fd *f, int *test)
// {
// 	// ft_putstr_fd("ok", 2);
// 	// ft_putstr_nbr(mp->count, 2);
// 	// int i = 0;
// 	if (mp->count == 0)
// 	{
// 		// close(test[0]);
// 		close(test[1]);
// 	}
// 	else if (mp->count == count_pipes(f->res))
// 	{
// 		close(test[(mp->count -1) * 2]);
// 	}
// 	else
// 	{
// 		close(test[(mp->count - 1) * 2]);
// 		// ft_putstr_nbr((mp->count -1) * 2, 2);
// 		close(test[((mp->count - 1) * 2) + 3]);
// 	}
// }

// void	parent_process_mult(t_mp *mp, int count, t_fd *f, int *test)
// {
// 	if (mp->count == 0)
// 		close(mp->fd[1]);
// 	else if (mp->count == count_pipes(f->res))
// 		close(test[(mp->count -1) * 2]);
// 	else
// 	{
// 		close(test[(mp->count - 1) * 2]);
// 		close(test[((mp->count - 1) * 2) + 3]);
// 	}
// 	// mp->fdd = mp->fd[0];
// 	mp->count++;
// 	if (mp->count == count)
// 	{
// 	// 	while (wait(NULL) >= 0)
// 			;
// 	}
// }

// int	handle_multipipes(t_fd *f, t_list *var_env, t_command *cmd, char **env)
// {
// 	t_mp	mp[1];
// 	int *test;

// 	init_mp(mp, 0, f);
// 	// pipe(mp->fd);
// 	int i = 0;
// 	test = malloc(sizeof(int) * (count_pipes(f->res) * 2));
// 	while (i < count_pipes(f->res))
// 	{
// 		int j = pipe(test + (i * 2));
// 		if (j == -1)
// 			ft_putstr_fd("error", 2);
// 		i++;
// 	}
// 	// mp->fdd = mp->fd[0];
// 	while (mp->count <= count_pipes(f->res))
// 	{
// 		mp->pid = fork();
// 		if (mp->pid == -1)
// 			return (0);
// 		else if (mp->pid == 0)
// 		{
// 			prep_fds(mp, f, test);
// 			go_instruction(end_redir(middle_pipe(f->res, mp->count), f),
// 				var_env, cmd, env);
// 			close_fds(mp, f, test);
// 			exit(mp->status);
// 		}
// 		mp->count++;
// 	}
// 		waitpid(mp->pid, &mp->status, 1);
// 			parent_process_mult(mp, count_pipes(f->res) + 1, f, test);
// 	if (WIFSIGNALED(mp->status) && g_sig.boolean != -1)
// 		g_sig.boolean++;

// 			// wait(NULL);

// 	return (0);
// }

typedef struct	s_test t_test;
struct	s_test
{
	char			**res;
	int				pipes[2];
	t_test	*prec;
	t_test 	*next;
};

typedef struct	s_mult
{
	t_list **var_e;
	t_command **cmd;
	char ***env;
	t_fd **f;
}				t_mult;

int exec_pipe(t_test *t, int j, t_mult *mul, int i)
{
	pid_t	pid;
	int		ret;
	int		status;

	ret = EXIT_FAILURE;
	if (pipe(t->pipes))
		return (-1);
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if (j != i && dup2(t->pipes[1], 1) < 0)
			return (-1);
		if (j != 0 && dup2(t->prec->pipes[0], 0) < 0)
			return (-1);
		go_instruction(end_redir(t->res, *mul->f), *mul->var_e, *mul->cmd, \
			*mul->env);
		exit(ret);
	}
	else
	{
		waitpid(pid, &status, 0);
		close(t->pipes[1]);
		if (j == i)
				close(t->pipes[0]);
		if (j != 0)
			close(t->prec->pipes[0]);
		// if (WIFEXITED(status))
		// 	ret = WEXITSTATUS(status);
	}
	return (ret);
}

t_test	*ft_lstlast2(t_test *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

t_test *get_prec(t_test *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back2(t_test **start, t_test *new)
{
	t_test	*last;

	if (!new)
		return ;
	if (*start == NULL)
	{
		*start = new;
		new->prec = NULL;
	}
	else
	{
		last = ft_lstlast2(*start);
		last->next = new;
		new->prec = last;
		new->next = NULL;
	}
}

t_test	*ft_lstnew2(char **res)
{
	t_test	*new;

	new = malloc(sizeof(t_test));
	if (!(new))
		return (NULL);
	new->res = copy_tabtab(res);
	new->next = NULL;
	new->prec = NULL;
	return (new);
}

int	handle_multipipes(t_fd *f, t_list *var_env, t_command *cmd, char **env)
{
	int i = count_pipes(f->res);
	int j = 0;
	t_test *t;
	t_test **start;
	t_mult mul[1];
	int ret;

	mul->var_e = &var_env;
	mul->cmd = &cmd;
	mul->env = &env;
	mul->f = &f;

	start = NULL;
	t = ft_lstnew2(middle_pipe(f->res, j));
	start = &t;
	j++;
	while (j <= i)
	{
		ft_lstadd_back2(start, ft_lstnew2(middle_pipe(f->res, j)));
		j++;
	}
	j = 0;
	while (j <= i)
	{
		ret = exec_pipe(t, j, mul, i);
		t = t->next;
		j++;
	}
	return (ret);
}
