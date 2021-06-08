/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 18:59:08 by budal-bi          #+#    #+#             */
/*   Updated: 2021/06/08 10:27:57 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		is_in_string(char *line, int index)
{
	int i;
	int s_q;
	int d_q;
	int s_q2;
	int d_q2;

	s_q = 0;
	d_q = 0;
	s_q2 = 0;
	d_q2 = 0;
	i = 0;
	while (i < index)
	{
		if ((line[i] == '\"' && i == 0) || (i && line[i] == '\"' && line[i - 1] != '\\'))
			d_q++;
		if ((line[i] == '\'' && i == 0) || (i && line[i] == '\'' && line[i - 1] != '\\'))
			s_q++;
		i++;
	}
	while (i < ft_strlen(line))
	{
		if ((line[i] == '\"' && i == 0) || (i && line[i] == '\"' && line[i - 1] != '\\'))
			d_q2++;
		if ((line[i] == '\'' && i == 0) || (i && line[i] == '\'' && line[i - 1] != '\\'))
			s_q2++;
		i++;
	}
	if ((!(d_q % 2 && d_q2 % 2) && (!(s_q % 2 && s_q2 % 2))) || (s_q == 0 && d_q == 0))
		return (0);
	return (1);
}

char	*cut_after_punct(char *dest, char *line, char *command)
{
	int		i;
	char	*buf;
	int		j;
	char	*tmp;

//	if ((ft_strchr_bis(line, ';') > 0 && line[ft_strchr_bis(line, ';') - 1] != '\\' && is_in_string(line, ft_strchr_bis(line, ';') - 1) == 0))
//		i = ft_strchr_bis(line, ';');
//	else
		i = ft_strlen(command);
//	j = check_ok_quote(line, i);
//	if (j == ft_strlen(line))
//		i = -1;
//	if (i == -1)
//	{
//		dest = NULL;
//		return (dest);
//	}
	dest = ft_substr(line, i + 1, ft_strlen(line) - i);
	return (dest);
}

char	**copy_tabtab(char **res)
{
	int		i;
	int		j;
	char	**dest;

	i = 0;
	j = 0;
	while (res[i])
		i++;
	if (!(dest = malloc(sizeof(char *) * (i + 1))))
		return (NULL);
	while (res[j])
	{
		dest[j] = ft_strdup(res[j]);
		j++;
	}
	dest[j] = NULL;
	return (dest);
}

int		count_tabs(char **res)
{
	int		j;

	j = 0;
	if (!res[j] || !res)
		return (j);
	while (res[j] != NULL)
		j++;
	return (j);
}

void	free_tabtab(char **res)
{
	int		i;

	i = 0;
	if (!res)
		return ;
	while (res[i] != NULL)
		free(res[i++]);
	free(res);
}

void	init_structs(t_command *cmd)
{
	cmd->path = NULL;
	cmd->index = 0;
	cmd->cmd_rv = 0;
	cmd->start = 0;
	cmd->ret = 0;
}
