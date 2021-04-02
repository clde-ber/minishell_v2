#include "minishell.h"

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
//    free(str);
    return (ret);
}

int is_valid_env_c(char c)
{
    if (ft_isalnum(c) || c == '_')
        return (1);
    return (0);
}

int is_valid_env(char *str)
{
    int i;
    int count;

    i = 0;
    count++;
    while (str[i])
    {
        if (str[i] == '_' || ft_isalnum(str[i]))
            count++;
        i++;
    }
    if (i == count)
        return (1);
    return (0);
}