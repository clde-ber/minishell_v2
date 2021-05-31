/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:00:41 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/30 09:55:02 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_front_a_back(char **res, char *path, t_list *var_env, char *old_pwd)
{
	int		k;
	int		i;
	int		count;
	char	*buf;
	int		j;

	j = 1;
	i = 0;
	k = 0;
	count = 0;
	buf = ft_strjoin(path, "/");
	while (i < ft_strlen(res[j]))
	{
		if ((k = count_back(res[j], &i)))
			cd_go_back(&i, k, &buf);
		else
			cd_go_front(res[j], &i, k, &buf);
	}
	if (buf[ft_strlen(buf) - 1] == '/')
		buf[ft_strlen(buf) - 1] = '\0';
	set_pwd_env(old_pwd, buf, var_env);
	return (buf);
}

char	*get_cwd(void)
{
	char	*path;

	if (!(path = malloc(sizeof(char) * 1000)))
		return (NULL);
	getcwd(path, 1000);
	return (path);
}

void	ft_cd_minus(char **res, t_list *var_env, t_command *cmd, char *old_pwd)
{
	char *str;

	str = NULL;
	cmd->cmd_rv = 0;
	if (ft_strlen(res[1]) == 2 && res[1][0] == '-' && res[1][1] == '-')
		chdir((str = replace_by_env_value(ft_strdup("$HOME"), var_env, cmd)));
	else if (res[1][0] == '-' && res[1][1] == '\0')
	{
		chdir((str = replace_by_env_value(ft_strdup("$OLDPWD"), var_env, cmd)));
		ft_putstr_fd(str, 1);
		ft_putstr_fd("\n", 1);
	}
	else
	{
		str = ft_strdup("");
		ft_putstr_fd("bash : cd : ", 1);
		ft_putstr_fd(res[1], 1);
		ft_putstr_fd(": invalid option\ncd: usage: cd\
[-L] [-P] [-e] [-@] [dir]\n", 1);
		cmd->cmd_rv = 2;
	}
	set_pwd_env(old_pwd, str, var_env);
	free(str);
	free(old_pwd);
}

void	set_root_path(char **buf, char **path, char **res, char **str)
{
	int i;

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
		printf("BUF %s\n", *buf);
		free(*path);
		if (res[1][0] == '/')
			*path = ft_strdup(ft_strchr(&res[1][1], '/'));
		else
			*path = ft_strdup(ft_strchr(res[1], '/'));
	}
	*str = ft_strdup(*path);
}

void	cd_failure(char **res, t_command *cmd, char *old_pwd, char *buf)
{
	cmd->cmd_rv = 0;
	printf("buf %s\n", buf);
//	if (ft_strcmp(, "") == 0)
//		cmd->cmd_rv = 1;
	if (chdir(buf) == -1)
	{
		chdir(old_pwd);
		ft_putstr_fd("bash : cd : ", 1);
		ft_putstr_fd(res[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		cmd->cmd_rv = 1;
	}
}
