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

/*
**Liste chainee for termcap
*/
/*typedef struct s_list t_list;
struct s_list{
    char *line;
    void *next;
    void *prec;
};*/

typedef struct s_list
{
    char *name;
    void *value;
    struct s_list *prec;
    struct s_list *next;
}               t_list;

//droit a variable globale comme ça? si oui tant mieux
extern t_list *var_env;

/*
**start_a_parse_bulle
*/
char *getcommand(char *str);
void    ft_pwd(char **res);
void    dispatch(char *str, char **env, t_list *var_env);
int ft_is_empty_string(char *str);

/*
**ft_split
*/
size_t	len_wd(char const *str, char *charset);
size_t	count_malloc(char const *s, char *str);
void		*ft_free(char **res, int j);
char			**ft_split(char const *s, char *str);

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
t_list *set_env(char **env, char **tab, t_list *var_env);
t_list *set_new_env(char **env, char **tab, t_list *var_env);
t_list	*unset(t_list *env, char **tab);
void print_env(char **tab, t_list *environ);


/*
**redir
*/
void    check_redir(char **res, char *output);
void    redir_file(char **res, char *output, int c);

/*
**echo
*/
void    ft_echo(char **res, t_list *var_env);

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
t_list ft_record(void *lst, void *str);
void	ft_lstiter(t_list *lst, t_list (*f)(void *, void *), char *str);

/*
**minishell_utils
*/
int ft_strchr_bis(const char *s, int c);
int check_word(char *str, char *to_find, int i);
int search_word(char *str, char *to_find);
int ft_isspace(char c);

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

#endif