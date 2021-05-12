#include "minishell.h"

sig = 0;

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

void	restore_fds(t_fd *f)
{
	close(0);
	close(1);
	dup2(f->save_in, 0);
	dup2(f->save_out, 1);
}

void	init_fds(t_fd *f)
{
	f->save_in = dup(STDIN_FILENO);
	f->save_out = dup(STDOUT_FILENO);
	f->save_pipe = NULL;
	f->num_pipe = 0;
	f->save_pipe_in = 127;
	f->save_pipe_out = 127;
	pipe(f->fds);
}

int    dispatch(char *str, char **env, t_list *var_env, t_command *cmd)
{
	char **res;
	char **parsed_res;
	int num;
	t_fd f[1];

	init_fds(f);
	if (ft_is_empty_string(str))
	{
		cmd->cmd_rv = 127;
		return (0);
	}
	else
	{	
		res = ft_split(str, "\t\n\r\v\f ");
		parsed_res = parse_res(res, var_env, cmd);
		num = redir_and_send(parsed_res, f, var_env, cmd, env);
		restore_fds(f);
		free_tabtab(res);
		// if (parsed_res);
		// 	free_tabtab(parsed_res);
		// if (f->save_pipe != NULL)
		// 	free_tabtab(f->save_pipe);
	}
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
	char *end;

 	line = NULL;
 	save = NULL;
 	buf = NULL;
	end = 0;
 	if (!(cmd = malloc(sizeof(t_command))))
 		return (0);
 	init_structs(cmd);
 	var_env = set_new_env(env, var_env, cmd);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
 	while (end == 0)
 	{
 		if (!(sig))
 			write(1, "***minishell*** > ", 18);
 		get_next_line(0, &line);
 		if ((ft_strcmp(line, "$?")))
 			cmd->cmd_rv = 0;
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
 	init_structs(cmd);
 	free(cmd->path);
 	free(cmd);
 	return (0);
}

char *end_line(char *current, t_save *save, t_term *term)
{
	restore_term(term);
	// int k = 0;
	// while (save->done[k])
	// 	ft_putstr_fd(save->done[k++], 1);
	if (current == NULL)
		current = ft_strdup("\0");
	// if (save->size == 0)
	// {
	// 	if (!(save->done = malloc(sizeof(char *) * 2)))
	// 		return (NULL);
	// 	save->done[0] = ft_strdup(current);
	// 	save->done[1] = NULL;
	// }
	// else
		save->done = save_input(current, save->done);
	write(1, "\n", 1);
	return (current);
}

char *go_line(t_save *save, t_term *term)
{
	char buf[2];
	char *term_type = getenv("TERM");
	char *current;
	char *buf1;

	init_term(term);
	current = NULL;
	save->where = -1;
	if (save->done)
		save->size = count_tabs(save->done);
	else
		save->size = 0;
	save->mtline = 0;
	get_cursor_space(term);
	while (read(0, buf, 1) != -1)
	{
		buf[1] = '\0';
		if (buf[0] == '\n' || (int)buf[0] == 13)
			return (end_line(current, save, term));
		else if ((int)buf[0] == 27)
			current = handle_arrow(term, save, current);
		else if ((int)buf[0] == 4)
		{
			restore_term(term);
			write(1, "\n", 1);
			exit(0);
		}
		else
		{
			save->mtline = 1;
			write(1, &buf[0], 1);
			if (current == NULL)
				current = ft_strdup(buf);
			else
			{
				buf1 = ft_strdup(current);
				free(current);
				current = ft_strjoin(buf1, buf);
				free(buf1);
			}
		}
		buf[0] = '\0';
	}
	return (NULL);
}

/*int main(int ac, char **av, char **env)
{
	char *line;
	char *command;
	t_list *var_env;
	t_command *cmd;
	t_save save[1];
	t_term term[1];
	char *buf;
	char *buf2;

	line = NULL;
	buf = NULL;
	if (!(cmd = malloc(sizeof(t_command))))
		return (0);
	init_structs(cmd);
	var_env = set_new_env(env, var_env, cmd);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	// get_cursor_space(term);
	save->done = NULL;
	// save->size = 0;
	while (1)
	{
		if (!(sig))
			write(1, "***minishell*** > ", 18);
		line = go_line(save, term);
		// restore_term(term);
		if ((ft_strcmp(line, "$?")))
			cmd->cmd_rv = 0;
		if (ft_strcmp(line, "exit") == 0) //builtin à coder
		{
			// restore_term(term);
			exit(0);
		}
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
	// restore_term(term);
	free_tabtab(save->done);
	ft_lstdel(var_env);
	init_structs(cmd);
	free(cmd->path);
	free(cmd);
	return (0);
}*/
