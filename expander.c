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

char *replace_by_env(char *trim, t_list *var_env, t_command *cmd)
{
    int i;
    char *tmp;

    i = 0;
    tmp = ft_strdup("");
    while (i < ft_strlen(trim))
    {
        if (is_valid_env_c(trim[i]))
        {
            tmp = ft_strjoin(tmp, get_string(&trim[i]));
            i += ft_strlen(get_string(&trim[i]));
        }
        else if (trim[i] == '$')
        {
            tmp = ft_strjoin(tmp, get_env(&trim[i + 1], var_env, cmd));
            i += cmd->index + 1;
        }
        else
            return (ft_strdup(""));
        cmd->index = 0;
    }
    return (tmp);
}

char *non_handled_commands(char *res, t_list *var_env, char **args, t_command *cmd)
{
    char *tmp;

    tmp = ft_strdup(res);
    tmp = ft_strtrim(tmp, "\"");
    if (is_handled_cmd(args[0]) == 0 && tmp[0] == '$')
        tmp = replace_by_env(tmp, var_env, cmd);
    return (ft_strtrim(tmp, "\'"));
}

char *handled_export(char *res, t_list *var_env, char **args, t_command *cmd)
{
    char *trim_first;
    char *trim_secd;

    trim_first = NULL;
    trim_secd = NULL;
    if ((ft_strchr(res, '=')))
    {
        trim_first = parse_path(res, '=')[0];
        trim_secd = parse_path(res, '=')[1];
    }
    else
    {
        trim_first = ft_strdup(res);
        trim_secd = ft_strdup("");
    }
    if (trim_first[0] != '\'')
        trim_first = ft_strtrim(trim_first, "\"");
    if (trim_secd[0] != '\'')
        trim_secd = ft_strtrim(trim_secd, "\"");
    trim_first = replace_by_env(trim_first, var_env, cmd);
    trim_secd = replace_by_env(trim_secd, var_env, cmd);
    return (ft_strjoin(ft_strjoin(trim_first, "="), trim_secd));
}

char *expander(char *res, t_list *var_env, char **args, t_command *cmd)
{
    char *tmp;
    char *trim_first;
    char *trim_secd;

    trim_first = NULL;
    trim_secd = NULL;
    cmd->index = 0;
    if (is_handled_cmd(args[0]) == 0)
        return (non_handled_commands(res, var_env, args, cmd));
    else
    {
        if (ft_strcmp(args[0], "export") == 0)
            return (handled_export(res, var_env, args, cmd));
        else if (ft_strcmp(args[0], "unset") == 0)
        {
            if (res[0] == '\'')
                res = ft_strtrim(res, "\'");
            else
                res = ft_strtrim(res, "\"");
            return (replace_by_env(res, var_env, cmd));
        }
    }
    return (ft_strdup("error"));
}

char **parse_first_arg(char **res, char **parsed_res, t_command *cmd, t_list *var_env)
{
    if (res[0] && res[0][0] == '\'')
        parsed_res[0] = expander(antislashes_a_quotes(ft_strtrim(res[0], "\'")), var_env, res, cmd);
    else if (res)
        parsed_res[0] = expander(antislashes_a_quotes(ft_strtrim(res[0], "\"")), var_env, res, cmd);
    return (parsed_res);
}

int strings_to_join(char **res, int i)
{
    if (((res[i][0] == '\'' && res[i][ft_strlen(res[i]) - 1] == '\'')
    || (res[i][0] == '\"' && res[i][ft_strlen(res[i]) - 1] == '\"'))
    && res[i + 1] && ft_strchr(res[i + 1], '='))
        return (1);
    return (0);
}

char **create_parsed_res(char **res)
{
    int i;
    char **parsed_res;

    parsed_res = NULL;
    i = 0;
    while (res[i])
        i++;
    if (!(parsed_res = malloc(sizeof(char *) * (i + 1))))
        return (0);
    return (parsed_res);
}

char **parse_res(char **res, t_list *var_env, t_command *cmd)
{
    int i;
    char **parsed_res;
    int j;

    parsed_res = create_parsed_res(res);
    i = 1;
    j = 1;
    parsed_res = parse_first_arg(res, parsed_res, cmd, var_env);
    while (res[i])
    {
        if ((strings_to_join(res, i)))
        {
            parsed_res[j] = expander(antislashes_a_quotes(ft_strjoin(res[i],
            res[i + 1])), var_env, res, cmd);
            i++;
        }
        else
            parsed_res[j] = expander(antislashes_a_quotes(res[i]), var_env, res, cmd);
        i++;
        j++;
    }
    parsed_res[j] = NULL;
    return (parsed_res);
}