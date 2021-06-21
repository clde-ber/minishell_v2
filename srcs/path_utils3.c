/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 06:56:53 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/17 16:05:53 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_no_arg(t_list *var_env, t_command *cmd)
{
	char	*path;
	char	*str;

	cmd->cmd_rv = 0;
	str = search_env_name("HOME", var_env);
	if (str)
	{
		path = replace_by_env_value(ft_strdup("$HOME"), var_env, cmd);
		chdir(path);
		free_string(path);
		free_string(str);
	}
	else
		cmd->cmd_rv = 1;
}

void	set_pwd_env(char *path, char *buf, t_list *var_env)
{
	while (var_env->next)
	{
		if (ft_strcmp(var_env->name, "OLDPWD") == 0)
		{
			free(var_env->value);
			var_env->value = ft_strdup(path);
		}
		if (ft_strcmp(var_env->name, "PWD") == 0)
		{
			free(var_env->value);
			var_env->value = ft_strdup(buf);
		}
		var_env = var_env->next;
	}
}

void	write_cd_option_error(char *res, t_command *cmd, char **str,
t_list *var_env)
{
	*str = search_env_value("OLDPWD", var_env);
	ft_putstr_fd("bash : cd : ", 2);
	ft_putstr_fd(res, 2);
	ft_putstr_fd(": invalid option\ncd: usage: cd [-L] [-P] [-e] [-@] \
[dir]\n", 2);
	cmd->cmd_rv = 2;
}

void	write_cd_minus_option(char **str, t_list *var_env)
{
	*str = search_env_value("OLDPWD", var_env);
	chdir(*str);
	ft_putstr_fd(*str, 2);
	ft_putstr_fd("\n", 2);
}

void	ft_pwd(char **res, t_command *cmd)
{
	char	*path;
	char	*buf;
	int		i;

	i = 0;
	path = malloc(sizeof(char) * 1000);
	if (!(path))
		return ;
	getcwd(path, 1000);
	buf = ft_strjoin(path, "\n");
	free(path);
	ft_putstr_fd(buf, 1);
	free(buf);
	cmd->cmd_rv = 0;
}