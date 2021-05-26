/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/28 13:55:45 by clde-ber          #+#    #+#             */
/*   Updated: 2021/05/26 09:40:09 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Functions that read each line from a specific file descriptor. Returns 0 when EOF is read and 1 when a line terminating '\n' is read.
** Fills a '\0'-terminating char * with all characters of the line except '\n'.
*/

#include "minishell.h"

static char		*ft_read_a_join(size_t i, char *buf, char **line)
{
	buf[i] = '\0';
	line[0] = join_a_free(line[0], buf);
	return (line[0]);
}

static char		*ft_update_left(char *left, char *buf, char **line)
{
	line[0][find_n(line[0], ft_strlen(line[0]))] = '\0';
	ft_memmove(left, buf + find_n(buf, BUFFER_SIZE) + 1, ft_strlen(buf +
	find_n(buf, BUFFER_SIZE)));
	return (line[0]);
}

static char		*ft_create_a_clear_left(char *left, char *buf, size_t size)
{
	int k;

	buf[0] = '\0';
	if (left)
	{
		k = find_n(left, size);
		if (k != -1)
			ft_memmove(left, left + k + 1, ft_strlen(left + k));
		else
			left[0] = '\0';
		return (left);
	}
	else
	{
		if (!(left = malloc(sizeof(char) * (size + 1))))
			return (0);
		left[0] = '\0';
		return (left);
	}
}

int				get_next_line(int fd, char **line)
{
	ssize_t		i;
	char		buf[BUFFER_SIZE + 1];
	static char *left;

	left = (!left) ? ft_create_a_clear_left(left, buf, BUFFER_SIZE) : left;
	line[0] = ft_strjoin(left, "");
	ft_create_a_clear_left(left, buf, BUFFER_SIZE);
	if (find_n(line[0], ft_strlen(line[0])) != -1)
	{
		line[0][find_n(line[0], ft_strlen(line[0]))] = '\0';
		return (1);
	}
	while (find_n(buf, BUFFER_SIZE) == -1 &&
	(i = read(fd, buf, BUFFER_SIZE)) > 0)
		line[0] = ft_read_a_join(i, buf, line);
	if (find_n(buf, BUFFER_SIZE) == -1 && i <= 0)
	{
		write(1, "\n", 1);
		exit(0);
	}
	line[0] = (i == 0) ? line[0] : join_a_free(line[0], buf);
	if (find_n(line[0], ft_strlen(line[0])) != -1)
	{
		line[0] = ft_update_left(left, buf, line);
		return (1);
	}
	line[0] = join_a_free(line[0], buf);
	free(left);
	left = 0;
	return (fd < 0 || read(fd, buf, 0) < 0 || BUFFER_SIZE <= 0) ? -1 : 0;
}