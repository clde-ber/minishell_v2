#include "minishell.h"

void    ft_pwd(char **res)
{
	char *path;
	char *buf;
	int i;

	i = 0;
	if (!(path = malloc(sizeof(char) * 1000)))
		return ;
	getcwd(path, 1000);
	buf = ft_strjoin(path, "\n");
	free(path);
	// if (check_redir(res, i++, buf) == 0)
	ft_putstr_fd(buf, 1);
}

int		count_back(char *str)
{
	int k;
	int j;

	k = 0;
	j = 0;
	while(str[j])
	{
		if (str[j] == '.' && str[j + 1] == '.')
		{
			j +=2;
			k +=1;
			if (str[j] == '/')
				j++;
			else
				return (k);
		}
		else
			return (k);
	}
	return (k);
}

char	*path_copy(char *buf, int m, int i, char **res)
{
	int j;

	j = 0;
	if (!(buf = malloc(sizeof(char) * m)))
		return (NULL);
	while (j < m)
	{
		buf[j] = res[i][j];
		j++;
	}
	buf[j] = '\0';
	return (buf);
}

char *minus_path(char **res, char *path, int i)
{
	int k;
	char *buf;
	int m;

	buf = NULL;
	k = count_back(res[i]);
	while (k > 0)
	{
		if (buf)
			free(buf);
		m = ft_strrchr(path, '/');
		if (m == 0)
			return (buf = ft_strdup("/"));
		else
			buf = path_copy(buf, m, i, res);
		k--;
	}
	return (buf);
}

char *get_cwd()
{
	char *path;

	if (!(path = malloc(sizeof(char) * 1000)))
		return (NULL);
	getcwd(path, 1000);
	return (path);
}

void    ft_cd(char **res)
{
	char *path;
	char *buf;
	char *buf2;

	if (!res[1])
	{
		write(1, "\n", 2);
		return;
	}
	path = get_cwd();
	if (res[1][0] == '.')
	{
		buf2 = ft_strjoin(path, "\0");
		buf = minus_path(res, buf2, 1);
	}
	else
	{
		buf2 = ft_strjoin(path, "/");
		buf = ft_strjoin(buf2, res[1]);
	}
	if (chdir(buf) == -1)
		ft_putstr_fd("FAIL", 1);
	free(path);
	free(buf);
	free(buf2);
}