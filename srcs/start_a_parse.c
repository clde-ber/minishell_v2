/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_a_parse.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 15:34:56 by budal-bi          #+#    #+#             */
/*   Updated: 2021/07/08 16:07:33 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

int	main(int ac, char *av[], char **env)
{
	char		*line;
	t_list		*var_env;
	t_command	cmd[1];
	t_term		term[1];

	init_vars_main(&line, &term->done, ac, av);
	init_structs(cmd);
	var_env = NULL;
	set_env_list(&var_env, env, cmd);
	signal(SIGINT, handle_signal);
	signal(SIGQUIT, handle_signal);
	while (1)
	{
		ft_putstr_fd("***minishell*** > ", 1);
		line = go_line(term);
		main_loop(line, env, var_env, cmd);
		g_sig.boolean = 0;
		line = NULL;
	}
	finish_line(cmd, term, var_env);
	return (0);
}
