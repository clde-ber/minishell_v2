/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 07:43:17 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/09 09:08:19 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **res, t_command *cmd)
{
	char	*path;
	char	*buf;
	int		i;

	i = 0;
	if (!(path = malloc(sizeof(char) * 1000)))
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
	free(path);
	free(buf);
	free(old_pwd);
	free(ret);
}

int		if_too_many_args(char **res, t_command *cmd)
{
	if (res[1] && res[2])
	{
		ft_putstr_fd("Too many arguments\n", 2);
		cmd->cmd_rv = 1;
		return (1);
	}
	return (0);
}

void	init_cd_strings(char **old_pwd, char **buf, char **ret, char *path)
{
	*old_pwd = ft_strdup(path);
	*buf = ft_strdup(path);
	*ret = NULL;
}

void	init_2_strings(char *path, char *str)
{
	path = NULL;
	str = NULL;
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
	if (if_too_many_args(res, cmd) || (res[1] && res[1][0] == '-'))
		return ;
	if (chdir((str = get_cwd()) == -1))
		path = replace_by_env_value(ft_strdup("$PWD"), var_env, cmd);
	init_cd_strings(&old_pwd, &buf, &ret, path);
	set_root_path(&buf, &path, res, &str);
	if (chdir(ret = cd_front_a_back(res[1], old_pwd, var_env, old_pwd)) == -1)
	{
		if ((chdir(res[1]) == -1))
			cd_failure(res, cmd, old_pwd, res[1]);
		else
			set_pwd_env(old_pwd, res[1], var_env);
	}
	else
		set_pwd_env(old_pwd, ret, var_env);
	free(str);
	free_cd(path, buf, old_pwd, ret);
}
