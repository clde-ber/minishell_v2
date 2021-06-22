/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils5.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 15:26:09 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/21 14:46:31 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	cmd->path = NULL;
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

	i = 0;
	while (var_env->next)
	{
		i++;
		var_env = var_env->next;
	}
	while (var_env->prec)
		var_env = var_env->prec;
	res = malloc(sizeof(char *) * (i + 2));
	if (!(res))
		return (0);
	i = 0;
	while (var_env->next)
	{
		res[i] = join_a_free(ft_strjoin(var_env->name, "="), var_env->value);
		var_env = var_env->next;
		i++;
	}
	res[i] = join_a_free(ft_strjoin(var_env->name, "="), var_env->value);
	res[i + 1] = NULL;
	return (res);
}