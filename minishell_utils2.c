#include "minishell.h"

char	*cut_after_punct(char *dest, char *line)
{
	int		i;
	char	*buf;

	i = ft_strchr_bis(line, ';');
	if (i == -1)
	{
		dest = NULL;
		return (dest);
	}
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
}
