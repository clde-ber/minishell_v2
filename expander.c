#include "minishell.h"

/*char *search_env_name(char *str, t_list *var_env)
{
    int chg;
    char *ret;

    chg = -1;
    while (var_env->next && chg == -1)
    {
        if (ft_strcmp(var_env->name, str) == 0)
        {
            ret = ft_strdup(var_env->name);
            return (ret);
        }
        var_env = var_env->next;
    }
    return (ft_strdup(""));
}*/

char *search_env_value(char *str, t_list *var_env)
{
    int chg;
    char *ret;

    chg = -1;
    while (var_env->next && chg == -1)
    {
        if (ft_strcmp(var_env->name, str) == 0)
        {
            ret = var_env->value;
            return (ret);
        }
        var_env = var_env->next;
    }
    return (NULL);
}
/*
char *ft_get_var_name(char *str)
{
    int i;
    char *res;
    int len;

    i = 0;
    while (str[i] && ft_isalnum(str[i]))
        i++;
    len = i;
    i = 0;
    if (!(res = malloc(sizeof(char) * (len + 1))))
        return (0);
    while (i < len)
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
    len = ft_strlen(str);
    if (str[len - 1] == '\"')
    {
        if (!(res = malloc(sizeof(char) * (len + 1))))
            return (0);
        while (i < len - 1)
        {
            res[i] = str[i];
            i++;
        }
        res[i] = '\0';
    }
    else
        res = ft_strdup(str);
    return (res); 
}*/

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
        if (str[i] == '\\' || str[i] == '\'' || str[i] == '\"')
            i++;
        ret[j] = str[i];
        j++;
        i++;
    }
    ret[j] = '\0';
    free(str);
    return (ret);
}

char *expander(char *res, t_list *var_env)
{
    int i;
    int len;
    char *str;
    char *to_free;
    char *to_free2;

    i = 0;
    len = ft_strlen(res);
    if (ft_strchr(res, '$') == NULL)
        return (ft_strdup(res));
    else if (res[0] == '\'' && res[len - 1] == '\'')
        return (ft_strtrim(res, "\'"));
    else
    {
        while (res[i + 1] && (!(res[i] == '$' && res[i + 1] != '$')))
            i++;
        if (res[0] == '\"' && res[len - 1] == '\"')
            to_free2 = ft_strtrim(&res[i], "$\"");
        else
            to_free2 = ft_strtrim(&res[i], "$");
        if (to_free = search_env_value(to_free2, var_env))
        {
            if (!(str = malloc(sizeof(char) * 255)))
                return (0);
            i = 0;
            while (to_free[i])
            {   
                str[i] = to_free[i];
                i++;
            }
            str[i] = '\0';
            free(to_free2);
        }
    }
    return (str);
}

char **parse_res(char **res, t_list *var_env)
{
    int i;
    char **parsed_res;
    int j;

    i = 0;
    while (res[i])
        i++;
    if (!(parsed_res = malloc(sizeof(char *) * (i + 1))))
        return (0);
    i = 0;
    while (res[i])
    {
        parsed_res[i] = expander(res[i], var_env);
        printf("%s\n", parsed_res[i]);
        i++;
    }
    parsed_res[i] = NULL;
    printf("%s\n", parsed_res[i]);
    return (parsed_res);
}