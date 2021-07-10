/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:31:38 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/09 21:09:22 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_location(char *arg)
{
	int		i;
	char	*res;

	res = ft_strdup(arg);
	if (ft_strlen(res) == 0)
		return (res);
	i = ft_strlen(res) - 1;
	while (i && res[i] == '/')
		i--;
	while (i && res[i] != '/')
		i--;
	res[i] = '\0';
	return (res);
}

char	*set_first_arg(char *p_bin, char *res)
{
	char	*str;
	char	*tmp;
	char	*ret;

	str = NULL;
	tmp = get_location(res);
	ret = NULL;
	if (!(ft_strnstr(p_bin, tmp, ft_strlen(p_bin))) \
	|| ft_strcmp(tmp, "") == 0)
	{
		str = ft_strjoin(p_bin, "/");
		ret = ft_strjoin(str, res);
	}
	else
		ret = ft_strdup(res);
	free(str);
	free(tmp);
	return (ret);
}

char	**arguments(char **res, int j, char **args, char *path)
{
	char	**argv;
	char	**p_bin;
	char	*str;
	int		i;
	int		k;

	init_2_vars(&i, &k);
	p_bin = parse_path(path, ':');
	argv = NULL;
	while (p_bin[k])
		k++;
	if (k)
		str = ft_strjoin(p_bin[0], "/");
	else
		str = ft_strdup("/");
	argv = malloc(sizeof(char *) * (j + 2));
	if (!(argv))
		return (0);
	argv[0] = ft_strjoin(str, res[0]);
	while (++i < j)
		argv[i] = ft_strdup(args[i - 1]);
	argv[i] = NULL;
	free(str);
	ft_free(p_bin, k + 1);
	return (argv);
}

char	**environment(char *path)
{
	char	**envp;

	envp = NULL;
	envp = malloc(sizeof(char *) * 2);
	if (!(envp))
		return (0);
	envp[0] = ft_strjoin("PATH=", path);
	envp[1] = NULL;
	return (envp);
}

void	write_error_shell(t_command *cmd, char **res)
{
	if (cmd->cmd_rv == 127)
	{
		if (ft_strcmp(cmd->path, "") == 0)
		{
			ft_putstr_fd("bash: ", 2);
			ft_putstr_fd(res[0], 2);
			ft_putstr_fd(": No such file or directory\n", 2);
		}
		else
		{
			ft_putstr_fd(res[0], 2);
			ft_putstr_fd(": Command not found\n", 2);
		}
	}
}
