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
	if (check_redir(res, i++, buf) == 0)
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
		}
	}
	return (k);
}

char *minus_path(char **res, char *path, int i)
{
	int j;
	int k;
	char *buf;
	char *buf2;
	int m;

	ft_putstr_fd(path, 1);
	k = count_back(res[i]);
	j = 0;
	ft_putstr_fd(res[i], 1);
	while (k > 0)
	{
		if (buf)
			free(buf);
		m = ft_strrchr(res[i], '/');
		// if (m == 0)
			// buf = ft_strdup("/");
		// else
		// {
			if (!(buf = malloc(sizeof(char) * m)))
				return (NULL);
			while (j < m)
			{
				write(1, "ping", 4);
				buf[j] = res[i][j];
				j++;
			}
			buf[j] = '\0';
			ft_putstr_fd(buf, 1);
		// }
		k--;
		j = 0;
	}
	ft_putstr_fd(buf, 1);
	return (buf);
}

void    ft_cd(char **res)
{
	char *path;
	char *buf;
	char *buf2;
	int i;
	
	i = 1;
	if (!res[i])
	{
		write(1, "\n", 2);
		return;
	}
	if (!(path = malloc(sizeof(char) * 1000)))
		return ;
	getcwd(path, 1000);
	// ft_putstr_fd(path, 1);
	if (res[i][0] == '.')
	{
		buf2 = ft_strjoin(path, "\0");
		buf = minus_path(res, buf2, i);
	}
	else
	{
		buf2 = ft_strjoin(path, "/");
		buf = ft_strjoin(buf2, res[i]);
	}
	ft_putstr_fd(buf, 1);
	if (chdir(buf) == -1)
		ft_putstr_fd("FAIL", 1);
	free(path);
	free(buf);
	free(buf2);
}