/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 07:43:17 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/28 10:47:21 by clde-ber         ###   ########.fr       */
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

char	*cd_front_a_back(char **res, char *path, int j, t_list *var_env, char *old_pwd)
{
	int		k;
	int		i;
	int		count;
	char	*buf;

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

void	ft_cd(char **res, t_list *var_env, t_command *cmd)
{
	char	*path;
	char	*buf;
	char	*buf2;
	char	*cut_path;
	int 	i;
	char	*str;
	char 	*old_pwd;
	char	*ret;

	// if (!res[1])
	// {
	// 	write(1, "\n", 2);
	// 	return ;
	// }
	i = 1;
	str = NULL;
	if (res[2])
	{
		ft_putstr_fd("Too many arguments\n", 2);
		cmd->cmd_rv = 1;
		return;
	}
	path = get_cwd();
	old_pwd = ft_strdup(path);
	if (res[1][0] == '-')
	{
		if (ft_strlen(res[1]) == 2 && res[1][0] == '-' && res[1][1] == '-')
		{
			chdir((str = replace_by_env_value(ft_strdup("$OLDPWD"), var_env, cmd)));
			free(str);
			cmd->cmd_rv = 0;
		}
		else if (res[1][0] == '-' && res[1][1] == '\0')
		{
			chdir((str = replace_by_env_value(ft_strdup("$OLDPWD"), var_env, cmd)));
			ft_putstr_fd(str, 1);
			ft_putstr_fd("\n", 1);
			free(str);
			cmd->cmd_rv = 0;
		}
		else
		{
			ft_putstr_fd("bash : cd : ", 1);
			ft_putstr_fd(res[1], 1);
			ft_putstr_fd(": invalid option\ncd: usage: cd\
[-L] [-P] [-e] [-@] [dir]\n", 1);
			cmd->cmd_rv = 2;
		}
		free(path);
		free(old_pwd);
		return ;
	}	
	buf = ft_strdup(path);
	if (ft_strchr(&res[1][1], '/'))
	{
		while (buf[i])
		{
			if (buf[i] == '/')
				buf[i] = '\0';
			i++;
		}
		chdir(buf);
		free(path);
		if (res[1][0] == '/')
			path = ft_strdup(ft_strchr(&res[1][1], '/'));
		else
			path = ft_strdup(ft_strchr(res[1], '/'));
	}
	buf2 = ft_strdup(path);
	if (chdir(buf = cd_front_a_back(res, (ret = join_a_free(buf, buf2)), 1, var_env, old_pwd)) == -1)
	{
		free(buf);
		buf = cd_front_a_back(res, buf2, 1, var_env, old_pwd);
		free(ret);
		free(buf2);
		chdir(buf);
	}
	else
	{
		free(ret);
		free(buf2);
	}
	printf("buf %s\n", buf);
	cmd->cmd_rv = 0;
	if (chdir(buf) == -1 && ft_strcmp(buf, ""))
	{
		chdir(old_pwd);
		ft_putstr_fd("bash : cd : ", 1);
		ft_putstr_fd(res[1], 1);
		ft_putstr_fd(": No such file or directory\n", 1);
		cmd->cmd_rv = 1;
		free(path);
		free(buf);
		free(old_pwd);
		return ;
	}
	free(path);
	free(buf);
	free(old_pwd);
}
