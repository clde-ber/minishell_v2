#include "minishell.h"

/*
** Functions that play the role of the expander. After all the arguments in the command line have been splited with ft_split, each argument is read
** according to whether it begins with ' " $ or whatever. A two dimensional array is returned to be used either in the fonctions that are shell commands
** recreated builtins or in the execve function.
*/

char *expander(char *res, t_list *var_env, char **args, t_command *cmd)
{
    char *trim;
    char *name;
    char *str;

    trim = NULL;
    name = NULL;
    str = NULL;
    cmd->index = 0;
    if (is_handled_cmd(args[0]) == 0 || ft_strcmp(args[0], "echo") == 0 ||
    ft_strcmp(args[0], "pwd") == 0 || ft_strcmp(args[0], "cd") == 0)
        return (non_handled_commands(res, var_env, cmd));
    else
    {
        if (ft_strcmp(args[0], "export") == 0 && ft_strcmp(res, "export"))
            return (handled_export(res, var_env, cmd));
        else if (ft_strcmp(args[0], "unset") == 0 && ft_strcmp(res, "unset"))
        {
            if (res[0] == '\'')
                trim = ft_strtrim(res, "\'");
            else
                trim = ft_strtrim(res, "\"");
            str = ft_strtrim(trim, "\'");
            name = ft_get_name(str);
            if (trim[0] == '\'')
            {
                free(name);
                free(trim);
                return (str);
            }
            else
            {
                free(name);
                free(str);
                trim = replace_by_env(trim, var_env, cmd, 0);
                if (trim)
                    return (trim);
                else
                {
                    cmd->cmd_rv = 0;
                    return(ft_strdup(""));
                }
            }
        }
    }
    return (ft_strdup(res));
}

char **parse_first_arg(char **res, char **parsed_res)
{
    if (res[0] && res[0][0] == '\'')
        parsed_res[0] = ft_strtrim(res[0], "\'");
    else if (res)
        parsed_res[0] = ft_strtrim(res[0], "\"");
    return (parsed_res);
}

int strings_to_join(char **res, int i)
{
    if (((res[i][0] == '\'' && res[i][ft_strlen(res[i]) - 1] == '\'')
    || (res[i][0] == '\"' && res[i][ft_strlen(res[i]) - 1] == '\"'))
    && res[i + 1] && ft_strchr(res[i + 1], '='))
        return (1);
    else if (ft_strchr(res[i], '=') == 0 && res[i + 1] && res[i + 1][0] == '=')
        return (-1);
    return (0);
}

char **create_parsed_res(char **res)
{
    int i;
    char **tmp;
    char **parsed_res;

    parsed_res = NULL;
    i = 0;
    while (res[i])
    {
        res[i] = antislashes_a_quotes(res[i]);
        i++;
    }
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
    i = 0;
    j = 0;
//    parsed_res = parse_first_arg(res, parsed_res);
    while (res[i])
    {
        if ((strings_to_join(res, i)) > 0)
        {
            parsed_res[j] = expander(ft_strjoin(res[i],
            res[i + 1]), var_env, res, cmd);
            i++;
        }
        else if ((strings_to_join(res, i)) == -1)
            parsed_res[j] = NULL;
        else
            parsed_res[j] = expander(res[i], var_env, res, cmd);
        if (parsed_res[j] == NULL)
        {
            ft_free(parsed_res, i + 1);
            return (NULL);
        }
        printf("parsed_res %s\n", parsed_res[j]);
        i++;
        j++;
    }
    parsed_res[j] = NULL;
    return (parsed_res);
}