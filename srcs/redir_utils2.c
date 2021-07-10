/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:17:22 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/10 09:35:19 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_valid_res_bis(char **str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (ft_strcmp(str[i], "|") == 0 || ft_strcmp(str[i], "<") == 0 || \
			ft_strcmp(str[i], ">") == 0 || ft_strcmp(str[i], ">>") == 0)
		{
			if (!str[i + 1])
				return (1);
			else if (ft_strcmp(str[i + 1], "|") == 0 || ft_strcmp(str[i + 1],
					"<") == 0 || ft_strcmp(str[i + 1], ">") == 0 || ft_strcmp(\
					str[i + 1], ">>") == 0)
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
	int		i;
	char	**tabl;

	i = 0;
	f->save_pipe = malloc(sizeof(char *) * ((count_tabs(f->res) - \
		chrtabtab(f->res, "|")) + 2));
	if (!f->save_pipe)
		return (NULL);
	tabl = malloc(sizeof(char *) * (chrtabtab(f->res, "|") + 2));
	if (!tabl)
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

void	parent_process(t_mp *mp, char *str)
{
	control_fds(mp, 1);
	if (ft_strcmp(str, "exit") == 0)
	{
		while (wait(NULL) >= 0)
			;
	}
}

int	go_pipe(t_fd *f, t_list *var_env, t_command *cmd, char **env)
{
	t_mp	mp[1];

	init_mp(mp, f);
	if (f->save_pipe[0] == NULL)
	{
		go_instruction(end_redir(mp->first, f), var_env, cmd, env);
		free_tabtab(f->save_pipe);
		return (1);
	}
	if (mp->pid == 0)
	{
		control_fds(mp, 0);
		go_instruction(end_redir(mp->first, f), var_env, cmd, env);
		exit(mp->status);
	}
	else if (mp->pid != -1)
	{
		if (WIFSIGNALED(mp->status) && g_sig.boolean != -1)
			g_sig.boolean++;
		waitpid(mp->pid, &mp->status, 1);
		parent_process(mp, f->save_pipe[0]);
		go_instruction(end_redir_pipe(copy_tabtab(f->save_pipe), f), var_env, \
			cmd, env);
	}
	return (end_pipe(f, mp));
}
