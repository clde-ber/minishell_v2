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
#include <signal.h>
#include <curses.h>
#include <term.h>

#define BUFFER_SIZE 50

typedef struct s_list
{
	char *name;
	void *value;
	struct s_list *prec;
	struct s_list *next;
}               t_list;

typedef struct s_fd
{
	int save_in;
	int save_out;
	char **save_pipe;
	int num_pipe;
	int save_pipe_in;
	int save_pipe_out;
	int fds[2];
}               t_fd;

typedef struct	s_term
{
	struct termios s_termios;
    struct termios s_termios_backup;
	int col;
	int li;
	int	x;
	int	y;
	int size;
}				t_term;

typedef struct s_command
{
	char *path;
	int index;
	int cmd_rv;
}               t_command;

int     pipe_fd(t_fd *f);

//A DELETE
// dans debug_to_delete
void	ft_putstr_nbr(int i, int fd);

/*
**start_a_parse_bulle
*/
char *getcommand(char *str);
void    ft_pwd(char **res);
int   dispatch(char *str, char **env, t_list *var_env, t_command *cmd);
int ft_is_empty_string(char *str);

/*
**ft_split
*/
size_t	len_wd(char *str, char *charset);
size_t	count_malloc(char *s, char *str);
void		*ft_free(char **res, int j);
char			**ft_split(char *s, char *str);
size_t parse_command(size_t i, char *str, int *res, char *charset);
int is_symbol(char c, char comp);

/*
**expander
*/
char **create_parsed_res(char **res);
int strings_to_join(char **res, int i);
char **parse_first_arg(char **res, char **parsed_res);
char *expander(char *res, t_list *var_env, char **args, t_command *cmd);
char **parse_res(char **res, t_list *var_env, t_command *cmd);

/*
**expander_utils
*/
char *get_string(char *str);
char *get_env(char *str, t_list *var_env, t_command *cmd);
char *get_env_value(char *str, t_list *var_env, t_command *cmd);
char *replace_by_env(char *trim, t_list *var_env, t_command *cmd, int boolean);
char *non_handled_commands(char *res, t_list *var_env, t_command *cmd);
char *handled_export(char *res, t_list *var_env, t_command *cmd);
char *replace_by_env_value(char *trim, t_list *var_env, t_command *cmd);
char *get_string_value(char *str);
char *find_op(char *str);

/*
**expander_utils2
*/
char *search_env_name(char *str, t_list *var_env);
char *search_env_value(char *str, t_list *var_env);
char *antislashes_a_quotes(char *str);
int is_valid_env_c(char c);

/*
**launch_exe
*/
int launch_exe(char *exe, char *path, char **env, t_command *cmd);
void find_exe(char *path, char **env, t_command *cmd);

/*
**launch_exe_utils
*/
char	*ft_get_filename(const char *s, int c);
char *get_path(char *path, char c);
char **arg_tab(char *exe, char *path, char **env);
char **env_tab(char *path);

/*
**env
*/
void set_env(char **tabl, t_list *var_env, t_command *cmd);
t_list *set_new_env(char **env, t_list *var_env, t_command *cmd);
void	unset(t_list *env, char **tabl);
void print_env(t_list *environ);

/*
**env_utils
*/
char *ft_get_name(char *str);
void check_doublons_cl(char **tabl, char *i_name, char *j_name, int j);
t_list *check_doublons(int k, int j, char **tabl, t_list *var_env);
void replace_env(char *tabl, t_list *var_env);
void add_to_env(char **tabl, int k, int l);

/*
**env_utils2
*/
char **fill_list(t_list *environ, char **list, int i);
char **sort_list(char **list, int i, int j);
void print_sorted_env(t_list *environ);
int is_valid_env_name(char *str);
int is_valid_env_name_c(char c);

/*
**env_utils3
*/
void add_to_env_k(char **tabl, char *i_name, int k, int l);
void add_to_env_l(char **tabl, char *j_name, int k, int l);
char *create_i_value(char *tab_k, char *i_value);
char *create_j_value(char *tab_l, char *j_value);

/*
**path
*/
void    ft_pwd(char **res);
char *minus_path(char **res, char *path, int i);
void    ft_cd(char **res);

/*
**redir
*/
char **destroy_res(char **res);
int     handle_pipe(t_fd *f);
void    line_after_pipe(char **res, int i, t_fd *f);
char    **save_after_pipe(char **res, t_fd *f);
char **check_redir_end(char **res, t_fd *f);
char **check_redir(char **res, t_fd *f);

/*
**redir_utils
*/
int    handle_fds(char **res, t_fd *f);
int     open_fds_out(char **res, int i, int m);
int     open_fds_in(char **res, int i);
int		count_pipes(char **res);
char	**end_redir(char **res, t_fd *f);

/*
**echo
*/
void	ft_echo(char **res, t_list *var_env);

/*
**echo_utils
*/
char	*echo_option(char *output, int option);
void	go_trim(char **res, int i, int c);
char	*get_word(char **res, int i, int j);

/*
**exec
*/
int set_args(char **res, char *path, t_command *cmd);
int exec_command(char **args, char **res, char *path, int j);
char **arguments(char **res, int i, char **args, char *path);
char **environment(char *path);
int exit_status(int status);

/*
**termcap
*/
char  **save_input(char *str, char **save);
void	restore_term(t_term *term);
void	get_cursor_pos(t_term *term, char **res);
void get_cursor_space(t_term *term);
void	init_term(t_term *term);

/*
**parse_path
*/
char **parse_path(char *s, char c);

/*
**sig_a_errors
*/
void errors(t_command *cmd);
void handle_signal(int code);

/*
**minishell_utils
*/
int ft_strchr_bis(const char *s, int c);
int check_word(char *str, char *to_find, int i);
int search_word(char *str, char *to_find);
int ft_isspace(char c);
int is_handled_cmd(char *str);

/*
**minishell_utils2
*/
char    **copy_tabtab(char **res);
void init_structs(t_command *cmd);
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
char	*ft_strjoin_free(char *s1, char *s2);
int ft_is_empty_string(char *str);
void	ft_putchar(char c);

/*
**libft_utils5
*/
int				ft_atoi(const char *str);

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
void ft_record(void *lst, void *cmd);
void	ft_lstiter(t_list *lst, void (*f)(void *, void *), t_command *cmd);
void ft_lstdel(t_list *lst);

extern int sig;

#endif