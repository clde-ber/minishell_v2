#include "minishell.h"

int ft_is_empty_string(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (ft_isspace(str[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}

char *getcommand(char *str)
{
	int i;
	int j;
	char *ret;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && str[i] != ';')
		i++;
	if (i == 0)
		return (NULL);
	if (i == ft_strlen(str))
		return (str);
	if (!(ret = malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

// trouve la fonction qui correspond a la commande.
// Problemes : ici trouve le mot cle sans difference de s'il est intégré a une autre commande ou pas.
// exemple: echo "pwd" > file pourrait trouver echo en premier.
// need parsing plus precis en lettre par lettre

void    dispatch(char *str, char **env, t_list *var_env, t_command *cmd)
{
	int i;
	char **res;
	char **parsed_res;
	char **tab;

	i = 0;
	if (ft_is_empty_string(str))
		res = ft_calloc(2, sizeof(char *));
	else
		res = ft_split(str, "\t\n\r\v\f ");
	while (res[i])
	{
		printf("%d|\n", i);
		printf("%s|\n", res[i]);
		i++;
	}
	parsed_res = (ft_is_empty_string(str)) ? ft_calloc(2, sizeof(char *)) : parse_res(res, var_env);
	// printf("command:%s\n", res[0]);
	// tab = redir_ext_check(res);
	i = 0;
	// ft_putstr_fd("mon res: ", 1);
	// while (tab[i])
	// {
	//     ft_putstr_fd(tab[i], 1);
	//     // printf("%s|\n", tab[i]);
	//     i++;
	// }
	if (ft_strcmp(res[0], "pwd") == 0)
		ft_pwd(res);
	else if (ft_strcmp(res[0], "echo") == 0)
		ft_echo(res, var_env);
	else if (ft_strcmp(res[0], "cd") == 0)
		ft_cd(res);
	else if (res[0][0] == '.' && res[0][1] == '/')
		find_exe(0, str, env);
	else if (ft_strcmp(res[0], "export") == 0)
	{
		check_doublons(env, parsed_res, var_env, cmd);
		set_env(env, parsed_res, var_env, cmd);
	}
	else if (ft_strcmp(res[0], "env") == 0)
		print_env(env, var_env);
	else if (ft_strcmp(res[0], "unset") == 0)
		unset(var_env, parsed_res);
	else
		set_args(tab, env, cmd->path);
//    ft_free(parsed_res, i + 1);
//    ft_free(res, i + 1);
}

char  **save_input(char *str, char **save)
{
	int i;
	char **buf;
	int j;

	j = 0;
	if (save == NULL)
	{
		i = 0;
		if (!(save = malloc(sizeof(char *) * 2)))
			return (NULL);
		save[i] = ft_strdup(str);
		save[i + 1] = NULL;
		return (save);
	}
	i = count_tabs(save);
	if (!(buf = malloc(sizeof(char *) * i + 2)))
		return (NULL);
	buf[j] = ft_strdup(str);
	while (save[j])
	{
		buf[j + 1] = ft_strdup(save[j]);
		j++;
	}
	buf[j + 1] = NULL;
	free_tabtab(save);
	return (buf);
}

int main(int ac, char **av, char **env)
{
	char *line;
	int end;
	char *command;
	t_list *var_env;
	t_command *cmd;
	char **to_free;
	char **save;
	char *buf;
	char *buf2;

	end = 0;
	line = NULL;
	save = NULL;
	buf = NULL;
	if (!(cmd = malloc(sizeof(t_command))))
		return (NULL);
	var_env = set_new_env(env, (to_free = ft_calloc(2, sizeof(char *))), var_env, cmd);
	while (end == 0)
	{
		write(1, "***minishell*** > ", 18);
		get_next_line(0, &line);
		save = save_input(line, save);
		if (ft_strcmp(line, "exit") == 0) //builtin à coder
			end = 1;
		buf = ft_strdup(line);
		while ((command = getcommand(buf)) != NULL)
		{
			dispatch(command, env, var_env, cmd);
			buf2 = cut_after_punct(buf2, buf);
			if (buf2 == NULL)
				buf = NULL;
			else
				buf = ft_strdup(buf2);
			free(buf2);
			free(command);
			command = NULL;
		}
		free(line);
		if (buf != NULL)
			free(buf);
	}
	ft_lstdel(var_env);
	ft_free(to_free, 2);
	free(cmd->path);
	free(cmd);
	return (0);
}