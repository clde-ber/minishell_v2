/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 15:17:08 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/22 15:42:59 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_vars_main(char **line, char ***term_done, int *g_sig_sig,
int *g_sig_boolean)
{
	*line = NULL;
	*term_done = NULL;
	*g_sig_sig = 0;
	*g_sig_boolean = 0;
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
