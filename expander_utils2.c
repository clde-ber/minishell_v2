#include "minishell.h"

/*
** Functions that help re-parsing all command line arguments. Output environment linked list names and values to be compared, check whether the syntax
** of an environment variable is correct and output strings without antislashes.
*/

char *search_env_name(char *str, t_list *var_env)
{
    int chg;
    char *ret;

    chg = -1;
    while (var_env && chg == -1)
    {
        if (ft_strcmp(var_env->name, str) == 0)
        {
            ret = ft_strdup(var_env->name);
            return (ret);
        }
        var_env = var_env->next;
    }
    return (NULL);
}

char *search_env_value(char *str, t_list *var_env)
{
    char *ret;

    ret = NULL;
    while (var_env)
    {
        if (ft_strcmp(var_env->name, str) == 0)
        {
            ret = ft_strdup(var_env->value);
            return (ret);
        }
        var_env = var_env->next;
    }
    return (ft_strdup(""));
}

char *antislashes_a_quotes(char *str)
{
    char *ret;
    int len;
    int i;
    int j;

    len = ft_strlen(str);
    i = 0;
    j = 0;
    if (!(ret = malloc(sizeof(char) * (len + 1))))
        return (0);
    while (i < len)
    {
        if (str[i] == '\\')
            i++;
        ret[j] = str[i];
        j++;
        i++;
    }
    ret[j] = '\0';
    free(str);
    str = NULL;
    return (ret);
}

int is_valid_env_c(char c)
{
    if (ft_isalnum(c) || c == '_' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
    || c == '\f' || c == ' ' || c == '+' || c == '\'')
        return (1);
    return (0);
}