/*
**All functions pertaining the echo implementation. WIP: echo doc disappears to be attributed to redirection functions.
** echo stdin goes into echo main and creates char *output to be passed if redirection exists or to be printed.
*/

#include "minishell.h"

char *get_word(char **res, int i, int j)
{
    char *str;
    int t;
    int k;

    t = 0;
    j++;
    k = j;
    while (ft_isspace(res[i][j]) == 0 && res[i][j] && res[i][j] != '\"')
    {
        t++;
        j++;
    }
    if (!(str = malloc(sizeof(char) * t + 1)))
        return (NULL);
    t = 0;
    while (ft_isspace(res[i][k]) == 0 && res[i][k] && res[i][k] != '\"')   
        str[t++] = res[i][k++];
    return (str);
}

void    change_str_env(t_list *var_env, char **res, int i, int j)
{
    char *str;
    int     chg;
    char *buf;

    chg = -1;
    if (res[i][0] == '\'' || (j != 1 && res[i][j - 1] == '\\'))
        return ;
    str = get_word(res, i, j);
    while (var_env->next)
    {
        if (ft_strcmp(var_env->name, str) == 0)
        {
            free(res[i]);
            res[i] = ft_strdup(var_env->value);
            chg = 1;
        }
        var_env = var_env->next;
    }
    if (chg == -1)
    {
        free(res[i]);
        res[i] = ft_strdup("");
    }
}

//WARNING should only replace first occurence of env

void    check_quote(t_list *var_env, char **res, int i)
{
    char *buf;
    int j;

    j = ft_strchr_bis(res[i], '$');
    if (j != -1)
        change_str_env(var_env, res, i, j);
    if (res[i][0] == '\"')
    {
        buf = ft_strtrim(res[i], "\"");
        free(res[i]);
        res[i] = ft_strdup(buf);
        free(buf);
    }
    else if(res[i][0] == '\'')
    {
        buf = ft_strtrim(res[i], "\'");
        free(res[i]);
        res[i] = ft_strdup(buf);
        free(buf);
    }
}

void    ft_echo(char **res, t_list *var_env)
{
    int option;
    int i;
    char *output;

    i = 1;
    output = NULL;
    if (strcmp(res[i], "-n") == 0)
    {
        option = 1;
        i++;
    }
    while(res[i] && strcmp(res[i], "|") != 0 && strcmp(res[i], ">") != 0 && strcmp(res[i], ">>") != 0 && strcmp(res[i], "<") != 0)
    {
        check_quote(var_env, res, i);
        if (output == NULL)
            output = ft_strdup(res[i]);
        else
        {
            output = ft_strjoin(output, " ");
            output = ft_strjoin(output, res[i]);
        }
        i++;
    }
    if (option == 0)
        output = ft_strjoin(output, "\n");
    ft_putstr_fd(output, 1);
}