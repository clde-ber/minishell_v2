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

char    *replace_word(char *repl, char *dest, char *str, int j)
{
    int k;
    char *buf;
    int i;
    int l;

    i = 0;
    k = 0;
    // write(1, "test", 4);
    if (!(buf = malloc(sizeof(char) * (ft_strlen(dest) - (ft_strlen(str) + 1) + ft_strlen(repl) + 1))))
        return (NULL);
    // write(1, "conf", 4);
    while (i != j)
    {
        buf[i] = dest[i];
        // write(1, &buf[i], 1);
        i++;
    }
    l = i;
    while (repl[k])
    {
        buf[i++] = repl[k++];
        // write(1, &buf[i -1], 1);
    }
    l += ft_strlen(str) + 1;
    while(dest[l])
    {
        buf[i++] = dest[l++];
        // write(1, &buf[i -1], 1);
    }
    buf[i] = '\0';
    free(dest);
    // ft_putstr_fd(buf, 1);
    dest = ft_strdup(buf);
    free(buf);
    return (dest);
}

void    change_str_env(t_list *var_env, char **res, int i, int j)
{
    char *str;
    int     chg;

    chg = -1;
    if (res[i][0] == '\'' || (j != 1 && res[i][j - 1] == '\\'))
        return ;
    str = get_word(res, i, j);
    while (var_env->next)
    {
        // ft_putstr_fd(res[i],1);
        if (ft_strcmp(var_env->name, str) == 0)
        {
            // free(res[i]);
            res[i] = replace_word(var_env->value, res[i], str, j);
            // write(1, "cc", 2);
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

void    go_trim(char **res, int i, int c)
{
    char *buf;

    if (c == 0)
    {
        buf = ft_strtrim(res[i], "\"");
        free(res[i]);
        res[i] = ft_strdup(buf);
        free(buf);
    }
    else if (c == 1)
    {
        buf = ft_strtrim(res[i], "\'");
        free(res[i]);
        res[i] = ft_strdup(buf);
        free(buf);
    }
}

void    check_quote(t_list *var_env, char **res, int i)
{
    int j;

    j = ft_strchr_bis(res[i], '$');
    while (j != -1)
    {
        change_str_env(var_env, res, i, j);
        j = ft_strchr_bis(res[i], '$');
        //write(1, "ll", 2);
    }
    // ft_putstr_fd(res[i],1);
    if (res[i][0] == '\"')
        go_trim(res, i, 0);
    else if(res[i][0] == '\'')
        go_trim(res, i, 1);
}

void    ft_echo(char **res, t_list *var_env)
{
    int option;
    int i;
    char *output;
    char *buf;

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
            buf = ft_strjoin(output, " ");
            free(output);
            // output = ft_strjoin(output, " ");
            output = ft_strjoin(buf, res[i]);
            free(buf);
        }
        i++;
    }
    if (option == 0)
    {
        buf = ft_strjoin(output, "\n");
        free(output);
        output = ft_strdup(buf);
        free(buf);
    }
    ft_putstr_fd(output, 1);
}