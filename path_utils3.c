/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/29 06:56:53 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/30 09:59:31 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    cd_no_arg(t_list *var_env, t_command *cmd)
{
    char *path;

    cmd->cmd_rv = 0;
    path = replace_by_env_value(ft_strdup("$HOME"), var_env, cmd);
    if (chdir(path) == -1)
        cmd->cmd_rv = 1;
    free(path);
}