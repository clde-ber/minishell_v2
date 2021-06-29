/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:17:08 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/28 11:54:53 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
