/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:17:08 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/05 13:11:15 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	init_vars_main(char **line, char ***term_done, int ac, char *argv[])
{
	*line = NULL;
	*term_done = NULL;
	g_sig.sig = 0;
	g_sig.boolean = 0;
	(void)ac;
	(void)argv;
}

void	restore_fds(t_fd *f)
{
	close(0);
	close(1);
	dup2(f->save_in, 0);
	dup2(f->save_out, 1);
	close(f->save_out);
	close(f->save_in);
}

void	init_fds(t_fd *f)
{
	f->save_in = dup(STDIN_FILENO);
	f->save_out = dup(STDOUT_FILENO);
	f->save_pipe = NULL;
}

char	*getcommand(char *str)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	j = 0;
	if (str == NULL)
		return (NULL);
	while (str[i] && ((str[i] != ';' || (str[i] == ';' && \
	(i && str[i - 1] == '\\'))) || is_in_string(str, i)))
		i++;
	ret = malloc(sizeof(char) * (i + 1));
	if (!(ret))
		return (NULL);
	while (j < i)
	{
		ret[j] = str[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

void	set_env_list(t_list **var_env, char **env, t_command *cmd)
{
	if (env && env[0] != NULL)
		*var_env = set_new_env(env, *var_env, cmd);
	else
		*var_env = ft_lstnew(ft_strdup(""), ft_strdup(""));
}
