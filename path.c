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

char *minus_path(char **res, char *path, int i)
{
	int k;
	int j;
	char *buf;
	char *buf2;
	int m;

	k = 0;
	j = 0;
	while(res[i][j])
	{
		if (res[i][j] == '.' && res[i][j + 1] == '.')
		{
			j +=2;
			k +=1;
			if (res[i][j] == '/')
				j++;
		}
	}
	while (k > 0)
	{
		m = ft_strrchr(res[i], '/');
		if (m == 0)
			buf = ft_strdup("/");
		else
		{
			if (!(buf = malloc(sizeof(char) * m)))
				return (NULL);
			j = 0;
			while (j < m)
				buf[j] = res[i][j++];
			buf[j] = '\0';
		}
		k--;
	}
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
	buf2 = ft_strjoin(path, "/");
	if (res[i][0] == '.')
		buf = minus_path(res, buf2, i);
	else
		buf = ft_strjoin(buf2, res[i]);
	if (chdir(buf) == -1)
		ft_putstr_fd("FAIL", 1);
	free(path);
	free(buf);
	free(buf2);
}