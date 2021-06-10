/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 07:43:17 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/10 14:49:17 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	free_cd(char *path, char *buf, char *old_pwd, char *ret)
{
	free_string(path);
	free_string(buf);
	free_string(old_pwd);
	free_string(ret);
}

int	if_too_many_args(char **res, t_command *cmd)
{
	if (res[1] && res[2])
	{
		ft_putstr_fd("Too many arguments\n", 2);
		cmd->cmd_rv = 1;
		return (1);
	}
	return (0);
}

void	init_cd_strings(char **str, char **buf, char **ret, char *path)
{
	*buf = ft_strdup(path);
	*ret = NULL;
}

void	init_2_strings(char *path, char *str)
{
	path = NULL;
	str = NULL;
}

void	set_current_path_cd(char **str, char **path, t_list *var_env,
t_command *cmd)
{
	*str = get_cwd();
	if (chdir(*str) == -1)
		*path = search_env_value("HOME", var_env);
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

	init_2_strings(path, str);
	ft_cd_minus(res, var_env, cmd, get_cwd());
	if ((if_too_many_args(res, cmd)) || (res[1] && res[1][0] == '-'))
		return ;
	set_current_path_cd(&old_pwd, &path, var_env, cmd);
	init_cd_strings(&str, &buf, &ret, path);
	set_root_path(&buf, &path, res, &str);
	ret = cd_front_a_back(res[1], path, var_env, old_pwd);
	if (chdir(ret) == -1)
	{
		if (chdir(res[1]) == -1)
			cd_failure(res, cmd, old_pwd, res[1]);
		else
			set_pwd_env(old_pwd, res[1], var_env);
	}
	else
		set_pwd_env(old_pwd, ret, var_env);
//	free_string(str);
	free_cd(path, buf, old_pwd, ret);
}
