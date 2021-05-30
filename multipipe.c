/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multipipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/08 17:47:58 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/29 13:23:39 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int i;
	int j;
	int fd[2];
	pid_t pid;
	int fdd;
	int status;

	j = 0;
	fdd = 0;
	pid = 0;
	while (j < count_pipes(f->res) + 1)
	{
		pipe(fd);
		if ((pid = fork()) == -1)
			exit(1);
		else if (pid == 0)
		{
			dup2(fdd, 0);
			if (j < count_pipes(f->res))
				dup2(fd[1], 1);
			close(fd[0]);
			go_instruction(end_redir(middle_pipe(f->res, j), f), var_env, cmd,
			env);
			exit(status);
		}
		waitpid(-1, &status, 0);
		close(fd[1]);
		fdd = fd[0];
		j++;
	}
}
