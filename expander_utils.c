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

char *get_string_value(char *str)
{
    int i;
    char *res;

    i = 0;
    res = NULL;
    if (!(res = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (0);
    while (str[i])
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
    char *ret;

    i = 0;
    if (!(test = malloc(sizeof(char) * (ft_strlen(str) + 1))))
        return (0);
    test[i] = '\0';
    while (str[i] && ft_strcmp((ret = search_env_value(test, var_env)), "") == 0)
    {
        test[i] = str[i];
        i++;
        test[i] = '\0';
        free(ret);
        ret = 0;
    }
    if (ret)
    {
        free(ret);
        ret = 0;
    }
    if (ft_strcmp((ret = search_env_value(test, var_env)), "") == 0)
    {
        free(ret);
        ret = ft_strdup("");
        free(test);
        return (ret);
    }
    else
    {
        cmd->index += ft_strlen(test);
        free(test);
        return (ret);
    }
}

char *replace_by_env(char *trim, t_list *var_env, t_command *cmd, int boolean)
{
    size_t i;
    char *tmp;
    char *str;

    i = 0;
    tmp = ft_strdup("");
    if (trim[0] == '\'')
    {
        str = ft_strjoin_free(tmp, trim);
        tmp = ft_strtrim(str, "\'");
        free(str);
        return (tmp);
    }
    while (i < ft_strlen(trim))
    {
        if (is_valid_env_c(trim[i]))
        {
            tmp = join_a_free(tmp, (str = get_string(&trim[i])));
            cmd->index += ft_strlen(str);
            i += ft_strlen(str);
            free(str);
        }
        else if (trim[i] == '$')
        {
            tmp = ft_strjoin_free(tmp, get_env(&trim[i + 1], var_env, cmd));
            i += cmd->index + 1;
        }
        else
        {
            if (boolean == 0)
                errors(cmd);
            free(trim);
            return (tmp);
        }
        cmd->index = 0;
    }
    free(trim);
    return (tmp);
}

char *replace_by_env_value(char *trim, t_list *var_env, t_command *cmd)
{
    size_t i;
    char *tmp;
    char *str;

    i = 0;
    tmp = ft_strdup("");
    if (trim[0] == '\'')
    {
        str = ft_strjoin_free(tmp, trim);
        tmp = ft_strtrim(str, "\'");
        free(str);
        return (tmp);
    }
    while (i < ft_strlen(trim))
    {
        if (trim[i] != '$')
        {
            tmp = join_a_free(tmp, (str = get_string_value(&trim[i])));
            cmd->index += ft_strlen(str);
            i += ft_strlen(str);
            free(str);
        }
        else
        {
            tmp = ft_strjoin_free(tmp, get_env(&trim[i + 1], var_env, cmd));
            i += cmd->index + 1;
        }
        cmd->index = 0;
    }
    free(trim);
    return (tmp);
}

char *non_handled_commands(char *res, t_list *var_env, t_command *cmd)
{
    char *tmp;
    char *tmp_sub;
    char *ret;

    tmp = ft_strdup(res);
    tmp_sub = ft_strtrim(tmp, "\"");
    ret = NULL;
    free(tmp);
    if (ft_strchr(tmp_sub, '$'))
        tmp_sub = replace_by_env(tmp_sub, var_env, cmd, 1);
    ret = ft_strtrim(tmp_sub, "\'");
    free(tmp_sub);
    return (ret);
}

char *handled_export(char *res, t_list *var_env, t_command *cmd)
{
    char *trim_first;
    char *trim_secd;
    char *str_first;
    char *str_secd;
    char *name;
    char *trim_cmp;
    char **p_bin;
    int i;

    i = 0;
    trim_first = NULL;
    trim_secd = NULL;
    str_first = NULL;
    str_secd = NULL;
    name = NULL;
    trim_cmp = NULL;
    p_bin = parse_path(res, '=');
    while (p_bin[i])
        i++;
    if ((ft_strchr(res, '=')))
    {
        str_first = ft_strdup(p_bin[0]);
        str_secd = ft_strdup(p_bin[1]);
    }
    else
    {
        str_first = ft_strdup(res);
        str_secd = ft_strdup("");
    }
    if (str_first[0] != '\'')
        trim_first = ft_strtrim(str_first, "\"");
    if (str_secd[0] != '\'')
        trim_secd = ft_strtrim(str_secd, "\"");
    free(str_first);
    free(str_secd);
    trim_first = replace_by_env(trim_first, var_env, cmd, 1);
    trim_secd = replace_by_env_value(trim_secd, var_env, cmd);
    trim_cmp = ft_strtrim(trim_first, "\'");
    name = ft_get_name(trim_cmp);
    if (is_valid_env_name(name) == 0)
    {
        printf("trim_first %s\n", name);
        ft_free(p_bin, i + 1);
        free(trim_first);
        free(trim_secd);
        free(name);
        free(trim_cmp);
        return (NULL);
    }
    str_first = ft_strtrim(trim_first, "\'");
    str_secd = ft_strtrim(trim_secd, "\'");
    free(trim_first);
    free(trim_secd);
    free(name);
    free(trim_cmp);
    ft_free(p_bin, i + 1);
    return (ft_strjoin_free(join_a_free(str_first, "="), str_secd));
}