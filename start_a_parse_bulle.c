#include "minishell.h"

int ft_is_empty_string(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if (ft_isspace(str[i]) == 0)
            return (0);
        i++;
    }
    return (1);
}

char *getcommand(char *str)
{
    int i;
    int j;
    char *ret;

    i = 0;
    j = 0;
    while (str[i] && str[i] != ';')
        i++;
    if (i == 0)
        return (NULL);
    if (!(ret = malloc(sizeof(char) * (i + 1))))
        return (NULL);
    while(j < i)
    {
        ret[j] = str[j];
        j++;
    }
    ret[j] = '\0';
    return (ret);
}

// trouve la fonction qui correspond a la commande.
// Problemes : ici trouve le mot cle sans difference de s'il est intégré a une autre commande ou pas.
// exemple: echo "pwd" > file pourrait trouver echo en premier.
// need parsing plus precis en lettre par lettre

void    dispatch(char *str, char **env, t_list *var_env, t_command *cmd)
{
    int i;
    char **res;
    char **parsed_res;

    i = 0;
    if (ft_is_empty_string(str))
        res = ft_calloc(2, sizeof(char *));
    else
        res = ft_split(str, "\t\n\r\v\f ");
    while (res[i])
    {
        printf("%d|\n", i);
        printf("%s|\n", res[i]);
        i++;
    }
    parsed_res = (ft_is_empty_string(str)) ? ft_calloc(2, sizeof(char *)) : parse_res(res, var_env);
    // printf("command:%s\n", res[0]);
    if (ft_strcmp(res[0], "pwd") == 0)
        ft_pwd(res);
    else if (ft_strcmp(res[0], "echo") == 0)
        ft_echo(res, var_env);
    else if (ft_strcmp(res[0], "cd") == 0)
        ft_cd(res);
    else if (res[0][0] == '.' && res[0][1] == '/')
        find_exe(0, str, env);
    else if (ft_strcmp(res[0], "export") == 0)
    {
        check_doublons(env, parsed_res, var_env, cmd);
        set_env(env, parsed_res, var_env, cmd);
    }
    else if (ft_strcmp(res[0], "env") == 0)
        print_env(env, var_env);
    else if (ft_strcmp(res[0], "unset") == 0)
        unset(var_env, parsed_res);
    else
        set_args(parsed_res, env, cmd->path);
//    ft_free(parsed_res, i + 1);
//    ft_free(res, i + 1);
}

// pour l'instant, ne prend qu'une commande. La commande doit etre enregistrée (pas fait), découpée (fait mais 
// rien n'est fait pour la suite de la commande) et envoyée a dispatch pour parsing.
int main(int ac, char **av, char **env)
{
    char *line;
    int end;
    char *command;
    t_list *var_env;
    t_command *cmd;
    char **to_free;
    // t_line save[2];


    end = 0;
    line = NULL;
    if (!(cmd = malloc(sizeof(t_command))))
        return (NULL);
    var_env = set_new_env(env, (to_free = ft_calloc(2, sizeof(char *))), var_env, cmd);
    while (end == 0)
    {
        write(1, "***minishell*** > ", 18);
        get_next_line(0, &line);
        if (ft_strcmp(line, "exit") == 0) //builtin à coder
            end = 1;
        if ((command = getcommand(line)) != NULL)
        {
            dispatch(command, env, var_env, cmd);
            free(command);
        }
        free(line);
    }
    ft_lstdel(var_env);
    ft_free(to_free, 2);
    free(cmd->path);
    free(cmd);
    return (0);
}