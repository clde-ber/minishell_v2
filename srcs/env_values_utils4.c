/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_values_utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/10 13:04:22 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/10 13:08:54 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*cmd_return_value(char **ret, t_command *cmd, char **test)
{
	*ret = rv_itoa(cmd->cmd_rv, *ret);
	cmd->index += 2;
	free_string(*test);
	return (*ret);
}
