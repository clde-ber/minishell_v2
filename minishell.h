#ifndef MINISHELL_H
#define MINISHELL_H

#include <stddef.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <fcntl.h>

#define BUFFER_SIZE 50

typedef struct s_list
{
    char *name;
    void *value;
    struct s_list *prec;
    struct s_list *next;
}               t_list;

typedef struct s_command
{
    char *path;
}               t_command;

//droit a variable globale comme ça? si oui tant mieux
extern t_list *var_env;

//A DELETE
// dans debug_to_delete
void	ft_putstr_nbr(int i, int fd);

/*
**start_a_parse_bulle
*/
char *getcommand(char *str);
void    ft_pwd(char **res);
void    dispatch(char *str, char **env, t_list *var_env, t_command *cmd);
int ft_is_empty_string(char *str);

/*
**ft_split
*/
size_t	len_wd(char const *str, char *charset);
size_t	count_malloc(char const *s, char *str);
void		*ft_free(char **res, int j);
char			**ft_split(char const *s, char *str);

/*
**expander
*/
char *search_env_name(char *str, t_list *var_env);
char *search_env_value(char *str, t_list *var_env);
char *antislashes_a_quotes(char *str);
char *expander(char *res, t_list *var_env, char **args);
char **parse_res(char **res, t_list *var_env);
int is_valid_env(char *str);

/*
**find_a_launch_exe
*/
char	*ft_get_filename(const char *s, int c);
char *get_path(char *path, char c);
int launch_exe(char *exe, char *path, char **env);
int find_exe(int index, char *path, char **env);

/*
**env
*/
char *ft_get_name(char *str);
void set_env(char **env, char **tab, t_list *var_env, t_command *cmd);
t_list *set_new_env(char **env, char **tab, t_list *var_env, t_command *cmd);
void	unset(t_list *env, char **tab);
void print_env(char **tab, t_list *environ);
void check_doublons(char **env, char **tab, t_list *var_env, t_command *cmd);

/*
**path
*/
void    ft_pwd(char **res);
char *minus_path(char **res, char *path, int i);
void    ft_cd(char **res);

/*
**redir
*/
char    **redir_ext_check(char **res);
int    check_redir(char **res, int i, char *output);
void    redir_file(char **res, int i, char *output, int c);

/*
**echo
*/
void    ft_echo(char **res, t_list *var_env);

/*
**exec
*/
int set_args(char **res, char **env, char *path);
int exec_command(char **args, char **res, char *path, int j);
int read_dir(char *path, char *command);

/*
**parse_path
*/
char **parse_path(char const *s, char c);

/*
**minishell_utils
*/
int ft_strchr_bis(const char *s, int c);
int check_word(char *str, char *to_find, int i);
int search_word(char *str, char *to_find);
int ft_isspace(char c);

/*
**minishell_utils2
*/
char    *cut_after_punct(char *dest, char *line);
int     count_tabs(char **res);
void    free_tabtab(char **res);

/*
**gnl
*/
int	get_next_line(int fd, char **line);

/*
**gnl_utils
*/
int		find_n(char *buf, size_t size);
char	*join_a_free(char *s1, char *s2);

/*
**libft_utils
*/
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);

/*
**libft_utils2
*/
int ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
int ft_ischarset(char *str, char c);

/*
**libft_utils3
*/
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);

/*
**libft_utils4
*/
int	ft_strlcpy(char *dst, const char *src, int dstsize);
int	ft_isalnum(int c);

/*
**libft_list
*/
void	ft_lstdelone(t_list *lst);
t_list	*ft_lstnew(char *name, void *value);
void	ft_lstadd_front(t_list **alst, t_list *new);
t_list	*ft_lstlast(t_list *lst);
void	ft_lstadd_back(t_list **alst, t_list *new);

/*
**libft_list2
*/
t_list ft_record(void *lst, void *str, void *cmd);
void	ft_lstiter(t_list *lst, t_list (*f)(void *, void *, void *), char *str, t_command *cmd);
void ft_lstdel(t_list *lst);


#endif