/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:02:13 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/28 15:02:25 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(char **res)
{
	char	*path;
	char	*buf;
	int		i;

	i = 0;
	if (!(path = malloc(sizeof(char) * 1000)))
		return ;
	getcwd(path, 1000);
	buf = ft_strjoin(path, "\n");
	free(path);
	ft_putstr_fd(buf, 1);
	free(buf);
}