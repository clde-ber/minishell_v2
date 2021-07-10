/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_values.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clde-ber <clde-ber@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/16 11:26:31 by clde-ber          #+#    #+#             */
/*   Updated: 2021/07/09 14:31:08 by clde-ber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	join_string_value(char **str, char **tmp, char *trim, int *index)
{
	(void)trim;
	*tmp = join_a_free(*tmp, *str);
	*index += ft_strlen(*str);
}

void	init_vars_replace_by_env(size_t *i, char **tmp, char **str)
{
	*i = 0;
	*tmp = ft_strdup("");
	*str = NULL;
}

int	is_not_env_value(size_t i, char *trim)
{
	if (!(((i && trim[i] == '$' && trim[i - 1] != '\\' && trim[i + 1] != '?') \
	|| (i == 0 && trim[i] == '$' && trim[i + 1] != '?')) && \
	(ft_isalnum(trim[i + 1]) || trim[i + 1] == '_')))
		return (1);
	return (0);
}

char	*remove_starting_spaces(char *str)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	j = 0;
	ret = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!(ret))
		return (0);
	while (str[i] && ft_isspace(str[i]))
		i++;
	while (str[i])
	{
		ret[j] = str[i];
		i++;
		j++;
	}
	ret[j] = '\0';
	free_string(str);
	return (ret);
}

char	*is_it_unknown_var(char *tmp)
{
	char	*str;

	str = antislashes_dolls(tmp);
	if (str)
		return (remove_starting_spaces(str));
	return (str);
}
