/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:00:41 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/02 14:12:38 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cd_front_a_back(char *res, char *path, char *old_pwd)
{
	int		k;
	int		i;
	char	*buf;

	i = 0;
	k = 0;
	buf = ft_strjoin(path, "/");
	while (i < (int)ft_strlen(res))
	{	
		k = count_back(res, &i);
		if (k)
			cd_go_back(k, &buf, old_pwd);
		else
			cd_go_front(res, &i, &buf);
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

void	ft_cd_minus(char **res, t_list *var_env, t_command *cmd, char *old_pwd)
{
	char	*str;

	str = NULL;
	if (chdir(old_pwd) == -1)
	{
		free_string(old_pwd);
		old_pwd = search_env_value("OLDPWD", var_env);
	}
	if (res[1] && res[1][0] == '-' && !(res[2]))
	{
		if (ft_strlen(res[1]) == 2 && res[1][0] == '-' && res[1][1] == '-')
		{
			str = search_env_value("HOME", var_env);
			chdir(str);
		}
		else if (res[1][0] == '-' && res[1][1] == '\0')
			write_cd_minus_option(&str, var_env);
		else
			write_cd_option_error(res[1], cmd, &str, var_env);
	}
	else
		str = search_env_value("OLDPWD", var_env);
	set_pwd_env(old_pwd, str, var_env);
	ft_free_2_strings(old_pwd, str);
}

void	set_root_path(char **buf, char **res)
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
	}
}

void	cd_failure(char **res, t_command *cmd, char *old_pwd)
{
	chdir(old_pwd);
	ft_putstr_fd("bash: cd: ", 2);
	ft_putstr_fd(res[1], 2);
	ft_putstr_fd(": No such file or directory\n", 2);
	cmd->cmd_rv = 1;
}
