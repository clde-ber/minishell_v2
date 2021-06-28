#include "../minishell.h"

t_sig	g_sig;

int	dispatch(char *str, char **env, t_list *var_env, t_command *cmd)
{
	char	**res;
	int		num;
	t_fd	f[1];

	(void)num;
	init_fds(f);
	if (ft_is_empty_string(str))
		return (0);
	else
	{	
		res = ft_split(str, "\t\n\r\v\f ");
		cmd->res = res;
		f->first_res = res;
		f->res = parse_res(res, var_env, cmd);
		g_sig.boolean = 1;
		num = redir_and_send(f, var_env, cmd, env);
		restore_fds(f);
		g_sig.stop = 0;
		free_tabtab(res);
		free_tabtab(f->res);
	}
	return (0);
}

int	ft_is_fail_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] != '>' && str[i] != '<' && str[i] != '|' && str[i] != ' ' \
			&& str[i] != ';')
			return (0);
		i++;
	}
	return (i);
}

void	main_loop(char *buf, char **env, t_list *var_env, t_command *cmd)
{
	char	*command;
	char	*buf2;

	if (buf == NULL)
	{
		free_string(buf);
		return ;
	}
	command = getcommand(buf);
	while (ft_strcmp(command, ""))
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
		ft_free_2_strings(buf2, command);
		command = getcommand(buf);
	}
	ft_free_2_strings(buf, command);
}

void	finish_line(t_command *cmd, t_term *term, t_list *var_env)
{
	free_tabtab(term->done);
	ft_lstdel(var_env);
	init_structs(cmd);
	free(cmd->path);
}

int	main(int ac, char **av, char **env)
{
	char		*line;
	t_list		*var_env;
	t_command	cmd[1];
	t_term		term[1];

	(void)ac;
	(void)av;
	init_vars_main(&line, &term->done, &g_sig.sig, &g_sig.boolean);
	init_structs(cmd);
	var_env = NULL;
	if ((env && env[0] != NULL) || !env)
		var_env = set_new_env(env, var_env, cmd);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		ft_putstr_fd("***minishell*** > ", 1);
		// while (g_sig.stop == 0)
			line = go_line(term);
		if (line && ft_strncmp(line, "exit", 4) == 0)
			ft_exit(0, ft_split(line, " \t\n\r\v\f"), cmd);
		main_loop(line, env, var_env, cmd);
		g_sig.boolean = 0;
		line = NULL;
	}
	finish_line(cmd, term, var_env);
	return (0);
}
