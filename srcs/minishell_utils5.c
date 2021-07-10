/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:26:09 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/06 22:34:26 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_tabs(char **res)
{
	int		j;

	j = 0;
	if (!res[j] || !res)
		return (j);
	while (res[j] != NULL)
		j++;
	return (j);
}

void	free_tabtab(char **res)
{
	int		i;

	i = 0;
	if (!res)
		return ;
	while (res[i] != NULL)
		free(res[i++]);
	free(res);
	res = NULL;
}

void	init_structs(t_command *cmd)
{
	cmd->path = ft_strdup("");
	cmd->index = 0;
	cmd->cmd_rv = 0;
	cmd->start = 0;
	cmd->ret = 0;
	cmd->bol = 0;
	cmd->res = NULL;
	cmd->env = NULL;
}

void	free_cd(char *path, char *buf, char *old_pwd, char *ret)
{
	free_string(path);
	free_string(buf);
	free_string(old_pwd);
	free_string(ret);
}

char	**put_list_in_tab(t_list *var_env)
{
	int		i;
	char	**res;
	t_list	*tmp;

	i = 0;
	tmp = var_env;
	while (var_env->next)
	{
		i++;
		var_env = var_env->next;
	}
	res = malloc(sizeof(char *) * (i + 2));
	if (!(res))
		return (0);
	i = 0;
	while (tmp->next)
	{
		res[i] = join_a_free(ft_strjoin(tmp->name, "="), tmp->value);
		tmp = tmp->next;
		i++;
	}
	res[i] = join_a_free(ft_strjoin(tmp->name, "="), tmp->value);
	res[i + 1] = NULL;
	return (res);
}
