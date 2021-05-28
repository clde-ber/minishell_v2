/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 07:43:17 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/28 15:22:54 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **res)
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
}

void	free_cd(char *path, char *buf, char *old_pwd)
{
	free(path);
	free(buf);
	free(old_pwd);
}

int		if_too_many_args(char **res, t_command *cmd)
{
	if (res[2])
	{
		ft_putstr_fd("Too many arguments\n", 2);
		cmd->cmd_rv = 1;
		return (1);
	}
	return (0);
}

void	init_cd_strings(char **path, char **old_pwd, char **buf, char **ret)
{
	*path = get_cwd();
	*old_pwd = ft_strdup(*path);
	*buf = ft_strdup(*path);
	*ret = NULL;
}

void	ft_cd(char **res, t_list *var_env, t_command *cmd)
{
	char	*path;
	char	*buf;
	char	*str;
	char	*old_pwd;
	char	*ret;

	if (if_too_many_args(res, cmd))
		return ;
	if (res[1][0] == '-')
	{
		ft_cd_minus(res, var_env, cmd);
		return ;
	}
	init_cd_strings(&path, &old_pwd, &buf, &ret);
	set_root_path(&buf, &path, res, &str);
	ret = join_a_free(buf, str);
	if (chdir(buf = cd_front_a_back(res, ret, var_env, old_pwd)) == -1)
	{
		free(buf);
		chdir((buf = cd_front_a_back(res, str, var_env, old_pwd)));
	}
	else
		free(str);
	cd_failure(res, cmd, old_pwd, buf);
	free_cd(path, buf, old_pwd);
}
