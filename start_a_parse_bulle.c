#include "minishell.h"

sig = 0;

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

void	restore_fds(t_fd *f)
{
	close(0);
	close(1);
	dup2(f->save_in, 0);
	dup2(f->save_out, 1);
}

int	end_check_pipe(char **tab, t_fd *f)
{
	restore_fds(f);
	if (f->save_pipe != NULL)
		return (1);
	return (0);
}

void	init_fds(t_fd *f)
{
	f->save_in = dup(STDIN_FILENO);
	f->save_out = dup(STDOUT_FILENO);
	f->save_pipe = NULL;
}

int    dispatch(char *str, char **env, t_list *var_env, t_command *cmd)
{
	int i;
	int j;
	char **res;
	char **parsed_res;
	char **tab;
	t_fd f[1];
	int end;

	init_fds(f);
	i = 0;
	j = 0;
	if (ft_is_empty_string(str))
    {
        cmd->cmd_rv = 127;
        return (0);
    }
	else
	{	
		res = ft_split(str, "\t\n\r\v\f ");
		parsed_res = parse_res(res, var_env, cmd);
		while (res[i])
		{
			printf("res %d|\n", i);
			printf("res %s|\n", res[i]);
			i++;
		}
		i = 0;
		end = 1;
		while (end == 1)
		{	
			tab = check_redir(parsed_res, f);
			if (ft_strcmp(tab[0], "pwd") == 0)
				ft_pwd(tab);
			else if (ft_strcmp(tab[0], "echo") == 0)
				ft_echo(tab, var_env);
			else if (ft_strcmp(tab[0], "cd") == 0)
				ft_cd(tab);
			if (tab[0][0] == '.' && tab[0][1] == '/')
				find_exe(str, env, cmd);
			else if (ft_strcmp(tab[0], "export") == 0 && tab[1] && parsed_res)
        	{
            	check_doublons_cl(parsed_res, NULL, NULL, 0);
            	set_env(parsed_res, var_env, cmd);
        	}
			else if (ft_strcmp(res[0], "export") == 0 && res[1])
            errors(cmd);
        	else if (ft_strcmp(res[0], "export") == 0 && (!(res[1])))
        	    print_sorted_env(var_env);
        	else if (ft_strcmp(res[0], "env") == 0)
        	    print_env(var_env);
        	else if (ft_strcmp(res[0], "unset") == 0 && parsed_res)
        	    unset(var_env, parsed_res);
			else if (ft_strcmp(res[0], "unset") == 0)
				errors(cmd);
        	else if (ft_strcmp(res[0], "$?"))
        	    set_args(parsed_res, cmd->path, cmd);
        	if (sig == 1)
        	    cmd->cmd_rv = 130;
        	if (sig == 2)
        	    cmd->cmd_rv = 131;
        	if (ft_strcmp(res[0], "$?") == 0)
        	    printf("%d : Command not found\n", cmd->cmd_rv);
        	if (sig == 1 || sig == 2)
        	    sig = 0;
			end = end_check_pipe(tab, f);
		}
		free_tabtab(tab);
		free_tabtab(res);
		free_tabtab(parsed_res);
	}
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
	if (!(buf = malloc(sizeof(char *) * (i + 2))))
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
	char *command;
	t_list *var_env;
	t_command *cmd;
	char **save;
	char *buf;
	char *buf2;

	line = NULL;
	save = NULL;
	buf = NULL;
	if (!(cmd = malloc(sizeof(t_command))))
		return (NULL);
	init_structs(cmd);
	var_env = set_new_env(env, var_env, cmd);
	while (1)
	{
		if (!(sig))
			write(1, "***minishell*** > ", 18);
		get_next_line(0, &line);
		if ((ft_strcmp(line, "$?")))
			cmd->cmd_rv = 0;
		save = save_input(line, save);
		if (ft_strcmp(line, "exit") == 0) //builtin à coder
			exit(0);
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
	init_structs(cmd);
	free(cmd->path);
	free(cmd);
	return (0);
}
