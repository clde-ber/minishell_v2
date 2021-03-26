#include "minishell.h"

char *search_env_name(char *str, t_list *var_env)
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
}

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
    return (ft_strdup(""));
}

char *ft_get_var_name(char *str)
{
    int i;
    char *res;
    int len;

    i = 0;
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
    int j;
    int k;
    char *str;
    char *to_free;
    char *to_free2;
    int boolean;

    i = 0;
    j = 0;
    k = 0;
    boolean = 0;
    if (!(str = malloc(sizeof(char) * 255)))
        return (0);
    len = ft_strlen(res);
    if (len > 1 && res[0] == '\"' && res[len - 1] == '\"')
    {
        j++;
        while (j < len - 1)
        {
            if (res[j] == '$' && res[j + 1] != '$')
            {
                j++;
                to_free2 = ft_get_var_name(&res[j]);
                to_free = search_env_value(to_free2, var_env);
                while (to_free[k])
                {   
                    str[i] = to_free[k];
                    k++;
                    i++;
                }
                j += ft_strlen(to_free2);
                k = 0;
                boolean = 1;
            }
            else
            {
                str[i] = res[j];
                i++;
                j++;
            }
        }
        if (boolean == 1)
            free(to_free2);
    }
    else if (len > 1 && res[0] == '\'' && res[len - 1] == '\'')
    {
        j++;
        while (j < len - 1)
        {
            if (i < len - 2)
            {
                str[i] = res[j];
                i++;
                j++;
            }
        }
    }
    else
    {
        while (j < len)
        {
            if (res[j] == '$' && res[j + 1] != '$')
            {
                j++;
                to_free2 = ft_get_var_name(&res[j]);
                to_free = search_env_value(to_free2, var_env);
                while (to_free[k])
                {   
                    str[i] = to_free[k];
                    k++;
                    i++;
                }
                j += ft_strlen(to_free2);
                k = 0;
                boolean = 1;
            }
            else
            {
                str[i] = res[j];
                i++;
                j++;
            }
        }
        if (boolean == 1)
            free(to_free2);
    }
    str[i] = '\0';
    str = antislashes_a_quotes(str);
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