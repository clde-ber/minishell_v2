#include "minishell.h"

t_sig g_sig;

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
}

int		dispatch(char *str, char **env, t_list *var_env, t_command *cmd)
{
	char **res;
	char **parsed_res;
	int num;
	t_fd f[1];

	init_fds(f);
	if (ft_is_empty_string(str))
		return (0);
	else
	{	
		res = ft_split(str, "\t\n\r\v\f ");
		int i;
		i = 0;
		while (res[i])
		{
			printf("%s\n", res[i]);
			i++;
		}
		f->res = parse_res(res, var_env, cmd);
		num = redir_and_send(f, var_env, cmd, env);
		restore_fds(f);
		free_tabtab(res);
		free_tabtab(f->res);
	}
}

void main_loop(char *buf, char **env, t_list *var_env, t_command *cmd)
{
	char *command;
	char *buf2;

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
}

void finish_line(t_command *cmd, t_term *term,t_list *var_env)
{
	free_tabtab(term->done);
	ft_lstdel(var_env);
	init_structs(cmd);
	free(cmd->path);
}

int main(int ac, char **av, char **env)
{
	char *line;
	t_list *var_env;
	t_command cmd[1];
	t_term term[1];
	int ret;

	line = NULL;
	ret = 0;
	init_structs(cmd);
	var_env = set_new_env(env, var_env, cmd);
	term->done = NULL;
	g_sig.sig = 0;
	g_sig.boolean = 0;
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		if (g_sig != 1 && g_sig != 2)
			write(1, "***minishell*** > ", 18);
		line = go_line(term);
		if (ft_strcmp(line, "exit") == 0) //builtin à coder
		{
			free(line);
			exit(0);
		}
		main_loop(ft_strdup(line), env, var_env, cmd);
		free(line);
		g_sig.boolean = 0;
	}
	finish_line(cmd, term, var_env);
	return (0);
}
