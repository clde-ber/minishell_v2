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
		// int i;
		// i = 0;
		// while (res[i])
		// {
		// 	printf("%s\n", res[i]);
		// 	i++;
		// }
		f->first_res = res;
		f->res = parse_res(res, var_env, cmd);
		num = redir_and_send(f, var_env, cmd, env);
		restore_fds(f);
		free_tabtab(res);
		free_tabtab(f->res);
	}
}

int ft_is_fail_char(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != ' ' &&
		str[i] != ';')
			return (0);
		i++;
	}
	return (i);
}

void main_loop(char *buf, char **env, t_list *var_env, t_command *cmd)
{
	char *command;
	char *buf2;

	if (buf == NULL)
	{
		free_string(buf);
		return ;
	}
	if (ft_is_fail_char(buf))
	{
		ft_putstr_fd("failed char\n", 2);
		// g_sig.sig = 2;
		free_string(buf);
		return ;
	}
	while (ft_strcmp((command = getcommand(buf)), ""))
	{
		dispatch(command, env, var_env, cmd);
		buf2 = cut_after_punct(buf2, buf, command);
		if (buf2 == NULL)
			free_string(buf);
		else
		{
			free_string(buf);
			buf = ft_strdup(buf2);
		}
		free_string(buf2);
		free_string(command);
	}
	free_string(buf);
	free_string(command);
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
		ft_putstr_fd("***minishell*** > ", 1);
		line = go_line(term);
		main_loop(line, env, var_env, cmd);
		g_sig.boolean = 0;
	}
	finish_line(cmd, term, var_env);
	return (0);
}