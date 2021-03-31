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
    return (NULL);
}

char *search_env_value(char *str, t_list *var_env)
{
    char *ret;

    while (var_env->next)
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

char *expander(char *res, t_list *var_env, char **args)
{
    int i;
    int len;
    char *str;
    char *to_free;
    char *to_free2;
    char *tmp;
    char *trim_first;
    char *trim_secd;

    i = 0;
    len = ft_strlen(res);
    trim_first = NULL;
    trim_secd = NULL;
    if (ft_strlen(res) == 2 && res[0] == '$' && res[1] == '$')
        return (ft_strdup(res));
    else if (res[0] == '\'' && ft_strcmp(args[0], "export") && ft_strcmp(args[0], "unset"))
        return (ft_strtrim(res, "\'"));
    else if (ft_strcmp(args[0], "export") && ft_strcmp(args[0], "unset"))
    {
        to_free2 = ft_strtrim(res, "\"");
        if (to_free2[0] == '$')
            return (search_env_value(parse_path(&to_free2[1], '$')[0], var_env));
        else
            return (parse_path(to_free2, '$')[0]);
    }
    else
    {
        if (ft_strchr(res, '=') && ft_strcmp(args[0], "export") == 0)
        {
            if (parse_path(res, '=')[0] && (!(parse_path(res, '=')[1])))
                return (ft_strdup(""));
            trim_first = parse_path(res, '=')[0];
            trim_secd = parse_path(res, '=')[1];
            printf("%s\n", trim_first);
            printf("%s\n", trim_secd);
            if (trim_first && trim_first[0] == '$')
                trim_first = search_env_value(parse_path(&trim_first[1], '$')[0], var_env);
            else if (trim_first && trim_first[0] != '\'')
                trim_first = parse_path(ft_strtrim(trim_first, "\""), '$')[0];
            if (trim_secd && trim_secd[0] == '\"')
            {
                write(1, "bbbb", 4);
                trim_secd = ft_strtrim(trim_secd, "\"");
            }
            else if (trim_secd && trim_secd[0] == '$')
            {
                write(1, "aaaa", 4);
                trim_secd = search_env_value(&trim_secd[1], var_env);
            }
            if (trim_first[0] == '$')
                trim_first = search_env_value(parse_path(&trim_first[1], '$')[0], var_env);
            else if (trim_first[0] == '\'')
            {
                if (is_valid_env(trim_first))
                    return (ft_strtrim(trim_first, "\'"));
                else
                {
                    write(1, "error", 5);
                    return (NULL);
                }
            }
            else
                parse_path(trim_first, '$')[0];
            if (trim_secd[0] == '$')
            {
                write(1, "cccc", 4);
                trim_secd = search_env_value(parse_path(&trim_secd[1], '$')[0], var_env);
            }
            else if (trim_secd[0] == '\'')
            {
                write(1, "eeee", 4);
                trim_secd = ft_strtrim(trim_secd, "\'");
            }
            else
            {
                write(1, "dddd", 4);
                trim_secd = parse_path(trim_secd, '$')[0];
            }
             printf("%s\n", trim_first);
            printf("%s\n", trim_secd);
            return (ft_strjoin(ft_strjoin(ft_strtrim(trim_first, "\'"), "="), ft_strtrim(trim_secd, "\'")));
        }
        else if (ft_strcmp(args[0], "export") == 0 && (!(ft_strchr(res, '='))))
            return (ft_strdup(""));
        else if (ft_strcmp(args[0], "unset") == 0)
        {
            if (res[0] != "\'")
                to_free2 = ft_strtrim(res, "\"");
            else
                to_free2 = ft_strdup(res);
            if (to_free2[0] == '$' && ft_strcmp(search_env_value(parse_path(&to_free2[1], '$')[0], var_env), ""))
                to_free2 = search_env_value(parse_path(&to_free2[1], '$')[0], var_env);
            else if (to_free2[0] == '$' && ft_strcmp(search_env_value(parse_path(&to_free2[1], '$')[0], var_env), "") == 0)
                to_free2 = NULL;
            else if (to_free2[0] == '\'' && is_valid_env(to_free2))
                return (ft_strtrim(to_free2, "\'"));
            else if (to_free2[0] == '\'' && (!(is_valid_env(to_free2))))
                to_free2 = NULL;
            else
                to_free2 = parse_path(to_free2, '$')[0];
            return (to_free2);
        }
    }
    return (ft_strdup(""));
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
    j = 0;
    while (res[i])
    {
        if (((res[i][0] == '\'' && res[i][ft_strlen(res[i]) - 1] == '\'')
        || (res[i][0] == '\"' && res[i][ft_strlen(res[i]) - 1] == '\"'))
        && res[i + 1] && ft_strchr(res[i + 1], '='))
        {
            parsed_res[j] = expander(antislashes_a_quotes(ft_strjoin(res[i], res[i + 1])), var_env, res);
            i++;
        }
        else
            parsed_res[j] = expander(antislashes_a_quotes(res[i]), var_env, res);
        printf("%s\n", parsed_res[j]);
        i++;
        j++;
    }
    parsed_res[j] = NULL;
    return (parsed_res);
}