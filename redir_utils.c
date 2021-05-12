#include "minishell.h"

int		open_fds_out(char **res, int i, int m)
{
	int		fd;

	i++;
	close(1);
	if (m == 0)
		fd = open(res[i], O_CREAT | O_RDWR | O_TRUNC, 0777);
	else 
		fd = open(res[i], O_APPEND | O_RDWR, 0777);
	return (fd);
}

int		open_fds_in(char **res, int i)
{
	int		fd;

	i++;
	close(0);
	fd = open(res[i], O_RDONLY, 0777);
	return (fd);
}

//check < redir si marche bien

int		handle_fds(char **res, t_fd *f)
{
	int		i;

	i = 0;
	while (res[i])
	{
		if (ft_strcmp(res[i], ">") == 0)
			return(open_fds_out(res, i, 0));
		else if (ft_strcmp(res[i], ">>") == 0)
			return(open_fds_out(res, i, 1));
		else if (ft_strcmp(res[i], "<") == 0)
			return(open_fds_in(res, i));
		i++;
	}
	return (-127);
}

int		count_pipes(char **res)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (res[i])
	{
		if (ft_strcmp(res[i], "|") == 0)
			j++;
		i++;
	}
	return (j);
}

char	**end_redir(char **res, t_fd *f)
{
	int		i;
	int		j;
	char	**tabl;

	i = 0;
	j = 0;
	if (chrtabtab(res, ">") == -1 && chrtabtab(res, ">>") == -1 && chrtabtab(res, "<") == -1)
		return (res);
	if (handle_fds(res, f) < 0)
	{
		restore_fds(f);
		return (NULL);
	}
	while (ft_strcmp(res[i], "<") != 0 && ft_strcmp(res[i], ">") != 0 && ft_strcmp(res[i], ">>") != 0)
		i++;
	if (!(tabl = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		tabl[j] = ft_strdup(res[j]);
		j++;
	}
	tabl[j] = NULL;
	return (tabl);
}
