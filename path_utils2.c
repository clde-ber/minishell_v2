/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:00:41 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/10 14:45:30 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_front_a_back(char *res, char *path, t_list *var_env, char *old_pwd)
{
	int		k;
	int		i;
	int		count;
	char	*buf;

	i = 0;
	k = 0;
	count = 0;
	buf = ft_strjoin(path, "/");
	while (i < ft_strlen(res))
	{	
		k = count_back(res, &i);
		if (k)
			cd_go_back(&i, k, &buf, old_pwd);
		else
			cd_go_front(res, &i, k, &buf);
	}
	if (ft_strlen(buf) > 1)
	{
		if (buf[ft_strlen(buf) - 1] == '/')
			buf[ft_strlen(buf) - 1] = '\0';
	}
	return (buf);
}

char	*get_cwd(void)
{
	char	*path;

	path = malloc(sizeof(char) * 1000);
	if (!(path))
		return (NULL);
	getcwd(path, 1000);
	return (path);
}

void	write_cd_option_error(char *res, t_command *cmd, char **str)
{
	*str = ft_strdup("");
	ft_putstr_fd("bash : cd : ", 1);
	ft_putstr_fd(res, 1);
	ft_putstr_fd(": invalid option\ncd: usage: cd [-L] [-P] [-e] [-@] \
[dir]\n", 1);
	cmd->cmd_rv = 2;
}

void	ft_cd_minus(char **res, t_list *var_env, t_command *cmd, char *old_pwd)
{
	char	*str;

	str = NULL;
	if (res[1] && res[1][0] == '-' && !(res[2]))
	{
		if (ft_strlen(res[1]) == 2 && res[1][0] == '-' && res[1][1] == '-')
		{
			str = replace_by_env_value(ft_strdup("$HOME"), var_env, cmd);
			chdir(str);
		}
		else if (res[1][0] == '-' && res[1][1] == '\0')
		{
			str = replace_by_env_value(ft_strdup("$OLDPWD"), var_env, cmd);
			chdir(str);
			ft_putstr_fd(str, 1);
			ft_putstr_fd("\n", 1);
		}
		else
			write_cd_option_error(res[1], cmd, &str);
		set_pwd_env(old_pwd, str, var_env);
	}
	else
		str = ft_strdup("");
	ft_free_2_strings(old_pwd, str);
}

void	set_root_path(char **buf, char **path, char **res, char **str)
{
	int	i;

	i = 1;
	if (ft_strchr(&res[1][1], '/'))
	{
		while ((*buf)[i])
		{
			if ((*buf)[i] == '/')
				(*buf)[i] = '\0';
			i++;
		}
		chdir(*buf);
		free(*path);
		if (res[1][0] == '/')
			*path = ft_strdup(ft_strchr(&res[1][1], '/'));
		else
			*path = ft_strdup(ft_strchr(res[1], '/'));
	}
}

void	cd_failure(char **res, t_command *cmd, char *old_pwd, char *buf)
{
	if (chdir(buf) == -1)
	{
		chdir(old_pwd);
		ft_putstr_fd("bash : cd : ", 1);
		ft_putstr_fd(res[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		cmd->cmd_rv = 1;
	}
}
