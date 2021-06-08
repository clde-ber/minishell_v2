/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 13:31:38 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/07 12:17:12 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_location(char *arg)
{
	int		i;
	char	*res;

	res = ft_strdup(arg);
	if (ft_strlen(res) == 0)
		return (res);
	i = ft_strlen(res) - 1;
	while (i && res[i] == '/')
		i--;
	while (i && res[i] != '/')
		i--;
	res[i] = '\0';
	return (res);
}

char	*set_first_arg(char *p_bin, char *res)
{
	char	*str;
	char	*tmp;
	char	*ret;

	str = NULL;
	tmp = NULL;
	ret = NULL;
	if (!(ft_strnstr(p_bin, (tmp = get_location(res)), ft_strlen(p_bin)))
	|| ft_strcmp(tmp, "") == 0)
	{
		str = ft_strjoin(p_bin, "/");
		ret = ft_strjoin(str, res);
	}
	else
		ret = ft_strdup(res);
	free(str);
	free(tmp);
	return (ret);
}