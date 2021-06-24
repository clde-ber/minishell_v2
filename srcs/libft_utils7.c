/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils7.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 16:21:07 by clde-ber          #+#    #+#             */
/*   Updated: 2021/06/24 03:32:26 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[i] != '\0' && len > 0)
	{
		while (haystack[i] && haystack[i + j] == needle[j]
			&& len > j)
		{
			if (needle[j + 1] == '\0')
				return ((char *)&haystack[i]);
			j++;
		}
		len--;
		j = 0;
		i++;
	}
	return (NULL);
}

int	faulty_redir(t_command *cmd)
{
	ft_putstr_fd("bash: synthax error near unexpected token 'newline'\n", 2);
	cmd->cmd_rv = 2;
	return (2);
}

void	control_fds(t_mp *mp, int i)
{
	if (i == 0)
	{
		close(mp->fd[0]);
		dup2(mp->fd[1], 1);
	}
	else
	{
		close(mp->fd[1]);
		dup2(mp->fd[0], 0);
	}
}
