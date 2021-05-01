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
		if (parsed_res);
			free_tabtab(parsed_res);
		if (f->save_pipe != NULL)
			free_tabtab(f->save_pipe);
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
	int end;

 	line = NULL;
 	save = NULL;
 	buf = NULL;
	end = 0;
 	if (!(cmd = malloc(sizeof(t_command))))
 		return (0);
 	init_structs(cmd);
 	var_env = set_new_env(env, var_env, cmd);
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

//get cursor space and set it after prompt before writing line, then at end of line

char *go_line(char **save)
{
	struct termios s_termios;
    struct termios s_termios_backup;
    char buf[2];
    char *term_type = getenv("TERM");
    char *end;
    char *buf1;
	int i;
	int col;
	int li;

	i = 0;
	end = NULL;
    tgetent(NULL, getenv("TERM"));
	tcgetattr(STDOUT_FILENO, &s_termios);
	tcgetattr(STDOUT_FILENO, &s_termios_backup);
	col = tgetnum("co");
	li = tgetnum("li");
    s_termios.c_lflag &= ~(ICANON);
    if (tcsetattr(0, 0, &s_termios) == -1)
        return (-1);
    s_termios.c_lflag &= ~(ECHO);
    while (read(0, buf, 1) > 0)
    {
        buf[1] = '\0';
        if (buf[0] == '\n')
        {
            if (end == NULL)
                end = ft_strdup("\0");
            return (end);
        }
        else if ((int)buf[0] == 27)
        {
            read(0, buf, 1);
            if ((int)buf[0] == 91)
            {
                read(0, buf, 1);
				//haut
                if ((int)buf[0] == 65)
				{
					i++;
					// tputs(tgoto(tgetstr("cm", NULL), g_info->cursor.posx, g_info->cursor.posy), 1, ft_putchar)
					ft_putstr_fd(save[i], 1);
				}
                    // write(1, "up", 2);
                else if ((int)buf[0] == 66)
				{
					i--;
					ft_putstr_fd(save[i], 1);
				}
                    // write(1, "do", 2);
                else
                    ;
            }
        }
        else
        {
            if (end == NULL)
                end = ft_strdup(buf);
            else
            {
                buf1 = ft_strdup(end);
                free(end);
                end = ft_strjoin(buf1, buf);
                free(buf1);
            }
        }
    }
	return (NULL);
}

/*int main(int ac, char **av, char **env)
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
		return (0);
	init_structs(cmd);
	var_env = set_new_env(env, var_env, cmd);
	while (1)
	{
		if (!(sig))
			write(1, "***minishell*** > ", 18);
		line = go_line(save);
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
}*/
