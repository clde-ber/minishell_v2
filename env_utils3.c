#include "minishell.h"

char *create_i_value(char *tab_k, char *i_value)
{
	if (ft_strchr(tab_k, '='))
		i_value = ft_strdup(ft_strchr(tab_k, '='));
	else
		i_value = ft_strdup("");
	return (i_value);
}
char *create_j_value(char *tab_l, char *j_value)
{
	if (ft_strchr(tab_l, '='))
		j_value = ft_strdup(ft_strchr(tab_l, '='));
	else
		j_value = ft_strdup("");
	return (j_value);
}

void add_to_env_l(char *tab_k, char *tab_l, char *i_name, char *j_name)
{
	char *i_value;
	char *j_value;

	i_value = create_i_value(tab_k, i_value);
	j_value = create_i_value(tab_l, j_value);
	if (ft_strchr(tab_l, '+') && ft_strchr(tab_k, '=') &&
	ft_strchr(tab_l, '='))
	{
		free(tab_l);
		tab_l = join_a_free(join_a_free(join_a_free(j_name, "\
+="), &i_value[1]), &j_value[1]);
		free(i_name);
	}
	else
	{
		free(i_name);
		free(j_name);
	}
	free(i_value);
	free(j_value);
}

void add_to_env_k(char **tab_k, char **tab_l, char *i_name, char *j_name)
{
	char *i_value;
	char *j_value;

	i_value = create_i_value(tab_k, i_value);
	j_value = create_i_value(tab_l, j_value);
	if (ft_strchr(tab_k, '+') && ft_strchr(tab_k, '=') &&
	ft_strchr(tab_l, '='))
	{
		free(tab_k);
		tab_k = join_a_free(join_a_free(join_a_free(i_name, "\
+="), &j_value[1]), &i_value[1]);
		free(j_name);
	}
	else
	{
		free(i_name);
		free(j_name);
	}
	free(i_value);
	free(j_value);
}