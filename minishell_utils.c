/*
**Useful functions created for minishell
**check word and search word detect keywords in commands
*/

#include "minishell.h"

int ft_strchr_bis(const char *s, int c)
{
	char	to_find;
	int		i;

	i = 0;
	to_find = c;
    printf("%s", s);
    write(1, "ok", 2);
	while (s[i])
	{
		if (s[i] == to_find)
			return (i);
		i++;
	}
    write(1, "ok", 2);
	if (c == '\0')
		return (i);
	return (-1);
}

int ft_isspace(char c)
{
    if (c == '\t' || c == '\n' || c == '\r' || c == '\v' || c == '\f' || c == ' ')
        return (1);
    return (0);
}

int check_word(char *str, char *to_find, int i)
{
    int j;

    j = 0;
    while (to_find[j])
    {
        if (str[i + j] == to_find[j])
            j++;
        else
            return (0);
    }
    return (1);
}

int search_word(char *str, char *to_find)
{
    int i;

    i = 0;
    while(str[i])
    {
        if (str[i] == to_find[0])
        {
            if (check_word(str, to_find, i) == 1)
                return (1);
        }
        i++;
    }
    return (0);
}