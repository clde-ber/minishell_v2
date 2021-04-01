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

int is_handled_cmd(char *str)
{
    if (ft_strcmp(str, "echo") == 0)
        return (1);
    if (ft_strcmp(str, "cd") == 0)
        return (1);
    if (ft_strcmp(str, "pwd") == 0)
        return (1);
    if (ft_strcmp(str, "export") == 0)
        return (1);
    if (ft_strcmp(str, "unset") == 0)
        return (1);
    if (ft_strcmp(str, "env") == 0)
        return (1);
    if (ft_strcmp(str, "exit") == 0)
        return (1);
    return (0);
}

char *get_string(char *str)
{
    int i;
    char *res;

    i = 0;
    res = NULL;
    if (!(res = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (0);
    while (str[i] && is_valid_env_c(str[i]))
    {
        res[i] = str[i];
        i++;
    }
    res[i] = '\0';
    return (res);
}

char *get_env(char *str, t_list *var_env, t_command *cmd)
{
    int i;
    char *test;

    i = 0;
    if (!(test = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (0);
    test[i] = '\0';
    while (str[i] && ft_strcmp(search_env_value(test, var_env), "") == 0)
    {
        test[i] = str[i];
        i++;
        cmd->index += i;
        test[i] = '\0';
    }
    if (ft_strcmp(search_env_value(test, var_env), "") == 0)
        return (ft_strdup(""));
    else
        return (search_env_value(test, var_env));
}

char *expander(char *res, t_list *var_env, char **args, t_command *cmd)
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
    tmp = ft_strdup("");
    cmd->index = 0;
    printf("res%s\n", res);
    if (is_handled_cmd(args[0]) == 0 && res[0] == '\'')
        return (ft_strtrim(res, "\'"));
    else if (is_handled_cmd(args[0]) == 0)
        return (ft_strtrim(res, "\""));
    else
    {
        if (ft_strcmp(args[0], "export") == 0)
        {
            write(1, "a", 1);
            if ((ft_strchr(res, '=')))
            {
                trim_first = parse_path(res, '=')[0];
                trim_secd = parse_path(res, '=')[1];
                write(1, "e", 1);
            }
            else
                trim_secd = ft_strdup("");
            if (trim_first[0] != '\'')
                trim_first = ft_strtrim(trim_first, "\"");
            if (trim_secd[0] != '\'')
                trim_secd = ft_strtrim(trim_secd, "\"");
            write(1, "b", 1);
            while (i < ft_strlen(trim_first))
            {
                if (is_valid_env_c(trim_first[i]))
                {
                    write(1, "c", 1);
                    tmp = ft_strjoin(tmp, get_string(&trim_first[i]));
                    i += ft_strlen(get_string(&trim_first[i]));
                }
                else if (trim_first[i] == '$')
                {
                    write(1, "d", 1);
                    tmp = ft_strjoin(tmp, get_env(&trim_first[i + 1], var_env, cmd));
                    i += cmd->index + 1;
                }
                else
                    return (ft_strdup(""));
                cmd->index = 0;
            }
            trim_first = tmp;
            tmp = ft_strdup("");
            i = 0;
            write(1, "x", 1);
            while (i < ft_strlen(trim_secd))
            {
                write(1, "x", 1);
                if (is_valid_env_c(trim_secd[i]))
                {
                    write(1, "x", 1);
                    tmp = ft_strjoin(tmp, get_string(&trim_secd[i]));
                    i += ft_strlen(get_string(&trim_secd[i]));
                }
                else if (trim_secd[i] == '$')
                {
                    write(1, "y", 1);
                    tmp = ft_strjoin(tmp, get_env(&trim_secd[i + 1], var_env, cmd));
                    i += cmd->index + 1;
                }
                else
                    return (ft_strdup(""));
                cmd->index = 0;
            }
            trim_secd = tmp;
            return (ft_strjoin(ft_strjoin(trim_first, "="), trim_secd));
        }
        else if (ft_strcmp(args[0], "unset") == 0)
        {
            if (res[0] == '\'')
                res = ft_strtrim(res, "\'");
            else
                res = ft_strtrim(res, "\"");
            while (res[i])
            {
                if (is_valid_env_c(res[i]))
                {
                    tmp = ft_strjoin(tmp, get_string(&res[i]));
                    i += ft_strlen(get_string(&res[i]));
                }
                else if (res[i] == '$')
                {
                    tmp = ft_strjoin(tmp, get_env(&res[i + 1], var_env, cmd));
                    i += cmd->index + 1;
                }
                else
                    return (ft_strdup(""));
            }
            return (ft_strdup(tmp));
        }
    }
    return (ft_strdup("error"));
}

char **parse_res(char **res, t_list *var_env, t_command *cmd)
{
    int i;
    char **parsed_res;
    int j;

    i = 0;
    while (res[i])
        i++;
    if (!(parsed_res = malloc(sizeof(char *) * (i + 1))))
        return (0);
    i = 1;
    j = 1;
    if (res[0] && res[0][0] == '\'')
        parsed_res[0] = ft_strtrim(res[0], "\'");
    else if (res[0])
        parsed_res[0] = ft_strtrim(res[0], "\"");
    while (res[i])
    {
        if (((res[i][0] == '\'' && res[i][ft_strlen(res[i]) - 1] == '\'')
        || (res[i][0] == '\"' && res[i][ft_strlen(res[i]) - 1] == '\"'))
        && res[i + 1] && ft_strchr(res[i + 1], '='))
        {
            parsed_res[j] = expander(antislashes_a_quotes(ft_strjoin(res[i], res[i + 1])), var_env, res, cmd);
            i++;
        }
        else
            parsed_res[j] = expander(antislashes_a_quotes(res[i]), var_env, res, cmd);
        printf("%s\n", parsed_res[j]);
        i++;
        j++;
    }
    parsed_res[j] = NULL;
    return (parsed_res);
}