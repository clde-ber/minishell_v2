/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/07 07:43:17 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/07 07:48:32 by clde-ber         ###   ########.fr       */
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
	// if (check_redir(res, i++, buf) == 0)
	ft_putstr_fd(buf, 1);
}

char	*cd_front_a_back(char **res, char *path, int j, t_list *var_env)
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
	set_pwd_env(path, buf, var_env);
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

void	ft_cd(char **res, t_list *var_env)
{
	char	*path;
	char	*buf;
	char	*buf2;

	if (!res[1])
	{
		write(1, "\n", 2);
		return ;
	}
	path = get_cwd();
	buf2 = ft_strjoin(path, "\0");
	buf = cd_front_a_back(res, buf2, 1, var_env);
	if (chdir(buf) == -1)
	{
		ft_putstr_fd("bash : cd : ", 1);
		ft_putstr_fd(res[1], 1);
		ft_putstr_fd(": No such file or directory", 1);
	}
	free(path);
	free(buf);
	free(buf2);
}
