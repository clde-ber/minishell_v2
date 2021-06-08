/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_exe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:53 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/07 07:04:17 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Functions that search and launch an executable when first command line
** agurment begins with "./". The program reads directories and compares
** their names to the ones in path. At the end, it checks whether the
** filename is correct or exists. If the last directory can't be opened,
** it returns an error. If execve - that executes the command - returns an
** error, it prints error accordingly. If command is interrupted by a signal,
** it prints an error.
*/

int		launch_exe(char *exe, char *path, char **env, t_command *cmd)
{
	pid_t	pid;
	int		ret;
	int		status;
	char	**argv;
	char	**envp;

	pid = 0;
	ret = 0;
	status = 0;
	argv = arg_tab(exe, path, env);
	envp = env_tab(path);
	if ((pid = fork()) == 0)
	{
		if ((ret = execve(argv[0], argv, envp)) == -1)
		{
			write(1, "bash: ", 6);
			write(1, path, ft_strlen(path));
			write(1, ": ", 2);
			printf("%s\n", strerror(errno));
			if (errno == 2)
				exit(127);
			if (errno == 13)
				exit(126);
		}
		else
			exit(status);
	}
	free_tabtab(envp);
	free_tabtab(argv);
	waitpid(ret, &status, 0);
	cmd->cmd_rv = status % 255;
	return (exit_status(status));
}

void	find_exe(char *path, char **env, t_command *cmd)
{
	DIR				*dir;
	char			*str;
	struct dirent	*st_dir;
	char			*path_mod;

	st_dir = NULL;
	str = ft_get_filename(path, '/');
	path_mod = get_path(path, '/');
	errno = 0;
	if (!(dir = opendir(path_mod)))
	{
		write(1, "bash: ", 6);
		write(1, path, ft_strlen(path));
		write(1, ": ", 2);
		printf("%s\n", strerror(errno));
		cmd->cmd_rv = 127;
		free(str);
		free(path_mod);
		return ;
	}
	while ((st_dir = readdir(dir)))
	{
		if (ft_strcmp(st_dir->d_name, str) == 0)
		{
			launch_exe(st_dir->d_name, path, env, cmd);
			closedir(dir);
			free(str);
			free(path_mod);
			return ;
		}
	}
	if (errno)
		printf("%s\n", strerror(errno));
	else
		launch_exe(str, path, env, cmd);
	closedir(dir);
	free(path_mod);
	free(str);
}
