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

int		count_back(char *str, int *j)
{
	int k;

	k = 0;
	while(*j < ft_strlen(str) && (str[*j] == '/'
	|| str[*j] == '.'))
	{
		while (str[*j] == '/')
			(*j)++;
		if (str[*j] == '.')
		{
			(*j)++;
			while (str[*j] == '.')
			{
				(*j)++;
				k++;
			}
		}
	}
	return (k);
}

void	path_copy(char **buf, int m, int k)
{
	int i;

	i = ft_strlen(*buf) - 1;
	while (i > 0 && k >= 0)
	{
		if ((*buf)[i] == '/')
		{
			(*buf)[i] = '\0';
			k--;
		}
		i--;
	}
}

void	cd_go_back(int *i, int k, char **buf)
{
	int m;

	m = 0;
	m = ft_strrchr(*buf, '/');
	if (m)
		path_copy(buf, m, k);
}

int		cd_go_front(char *res, int *i, int k, char **buf)
{
	int index;
	int count;

	count = 0;
	index = *i;
	if ((*buf)[ft_strlen(*buf) - 1] != '/')
		*buf = join_a_free(join_a_free(*buf, "/"), &res[index]);
	else
		*buf = join_a_free(*buf, &res[index]);
	while ((*buf)[count] && (*buf)[count] != '.')
		count++;
	while ((*buf)[count])
	{
		(*buf)[count] = '\0';
		count++;
	}
	while (res[*i] && res[*i] != '.')
		(*i)++;
}


char *minus_path(char **res, char *path, int j)
{
	int k;
	int i;
	int tmp;
	int count;
	char *buf;
	int m;

	i = 0;
	k = 0;
	count = 0;
	buf = ft_strjoin(path, "/");
	while (i < ft_strlen(res[j]))
	{
		if ((k = count_back(res[j], &i)))
		{	cd_go_back(&i, k, &buf);
		printf("buf %s\n", buf);
		printf("i %d\n", i);}
		else
		{	cd_go_front(res[j], &i, k, &buf);
		printf("buf %s\n", buf);
		printf("i %d\n", i);}
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
	buf2 = ft_strjoin(path, "\0");
	buf = minus_path(res, buf2, 1);
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