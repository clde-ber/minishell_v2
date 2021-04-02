#include "minishell.h"

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