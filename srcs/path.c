/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 07:43:17 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	if_too_many_args(char **res, t_command *cmd)
{
	if (res[1] && res[2])
	{
		ft_putstr_fd("bash: cd: too many arguments\n", 2);
		cmd->cmd_rv = 1;
		return (1);
	}
	return (0);
}

void	init_cd_strings(char **buf, char **ret, char *path)
{
	*buf = ft_strdup(path);
	*ret = NULL;
}

void	init_2_strings(char **path, char **str)
{
	*path = NULL;
	*str = NULL;
}

void	set_current_path_cd(char **str, char **path, t_list *var_env)
{
	*str = get_cwd();
	if (chdir(*str) == -1)
	{
		*path = search_env_value("PWD", var_env);
		free_string(*str);
		*str = ft_strdup(*path);
	}
	else
		*path = ft_strdup(*str);
}

void	ft_cd(char **res, t_list *var_env, t_command *cmd)
{
	char	*path;
	char	*buf;
	char	*str;
	char	*old_pwd;
	char	*ret;

	cmd->cmd_rv = 0;
	init_2_strings(&path, &str);
	ft_cd_minus(res, var_env, cmd, get_cwd());
	if ((if_too_many_args(res, cmd)) || (res[1] && res[1][0] == '-'))
		return ;
	set_current_path_cd(&old_pwd, &path, var_env);
	init_cd_strings(&buf, &ret, path);
	set_root_path(&buf, res);
	ret = cd_front_a_back(res[1], path, old_pwd);
	if (chdir(ret) == -1)
	{
		if (chdir(res[1]) == -1)
			cd_failure(res, cmd, old_pwd);
		else
			set_pwd_env(old_pwd, res[1], var_env);
	}
	else
		set_pwd_env(old_pwd, ret, var_env);
	free_cd(path, buf, old_pwd, ret);
}
