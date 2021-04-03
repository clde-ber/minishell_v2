#include "minishell.h"

/*
** Functions that replace any occurences of $ with existing environment variable name.
*/

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