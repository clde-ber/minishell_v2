/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: budal-bi <budal-bi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 22:13:10 by budal-bi          #+#    #+#             */
/*   Updated: 2021/05/12 13:46:24 by budal-bi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*replace_word(char *repl, char *dest, char *str, int j)
{
	int k;
	char *buf;
	int i;
	int l;

	i = 0;
	k = 0;
	if (!(buf = malloc(sizeof(char) * (ft_strlen(dest) - (ft_strlen(str) + 1) 
+ ft_strlen(repl) + 1))))
		return (NULL);
	while (i != j)
	{
		buf[i] = dest[i];
		i++;
	}
	l = i;
	while (repl[k])
		buf[i++] = repl[k++];
	l += ft_strlen(str) + 1;
	while(dest[l])
		buf[i++] = dest[l++];
	buf[i] = '\0';
	free(dest);
	dest = ft_strdup(buf);
	free(buf);
	return (dest);
}

void    change_str_env(t_list *var_env, char **res, int i, int j)
{
	char *str;
	int     chg;

	chg = -1;
	if (res[i][0] == '\'' || (j != 1 && res[i][j - 1] == '\\'))
		return ;
	str = get_word(res, i, j);
	while (var_env->next && chg == -1)
	{
		if (ft_strcmp(var_env->name, str) == 0)
		{
			res[i] = replace_word(var_env->value, res[i], str, j);
			chg = 1;
		}
		var_env = var_env->next;
	}
	//devrait faire \n plutot que chaine vide?
	if (chg == -1)
	{
		free(res[i]);
		res[i] = ft_strdup("");
	}
}

void	check_quote(t_list *var_env, char **res, int i)
{
	int j;

	j = ft_strchr_bis(res[i], '$');
	while (j != -1)
	{
		change_str_env(var_env, res, i, j);
		j = ft_strchr_bis(res[i], '$');
	}
	if (res[i][0] == '\"')
		go_trim(res, i, 0);
	else if(res[i][0] == '\'')
		go_trim(res, i, 1);
}

//check si multiquote pas de mvt sur les env
void	ft_echo(char **res, t_list *var_env)
{
	int		option;
	int		i;
	char	*output;
	char **buf;

	buf = copy_tabtab(res);
	i = 1;
	output = NULL;
	option = 0;
	if (buf[i] && ft_strcmp(buf[i], "-n") == 0)
	{
		option = 1;
		i++;
	}
	while (buf[i])
	{
		if (output == NULL)
			output = ft_strdup(buf[i]);
		else
		{
			output = ft_strjoin_free(output, ft_strdup(" "));
			output = ft_strjoin_free(output, ft_strdup(buf[i]));
		}
		i++;
	}
	free_tabtab(buf);
	output = echo_option(output, option);
	ft_putstr_fd(output, 1);
	free(output);
}
