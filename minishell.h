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

typedef struct	s_sig
{
	int			sig;
	int			boolean;
}				t_sig;

typedef struct	s_list
{
	char		*name;
	void		*value;
	struct		s_list *prec;
	struct		s_list *next;
}				t_list;

typedef struct	s_fd
{
	int			save_in;
	int			save_out;
	char		**save_pipe;
	char		**res;
}				t_fd;

typedef struct	s_term
{
	struct		termios s_termios;
	struct		termios s_termios_backup;
	int			x;
	int			y;
	int			col;
	int			lin;
	int			size;
	char		**done;
	char		*last;
	int			len;
	int			where;
	int			mtline;
}				t_term;

typedef struct s_command
{
	char		*path;
	int			index;
	int			cmd_rv;
	int			start;
	int			ret;
}				t_command;


int ft_is_fail_char(char *str);
//A DELETE
// dans debug_to_delete
void	ft_putstr_nbr(int i, int fd);

/*
**start_a_parse_bulle
*/
char	*getcommand(char *str);
void	restore_fds(t_fd *f);
void	init_fds(t_fd *f);
int		dispatch(char *str, char **env, t_list *var_env, t_command *cmd);
char	*go_line(t_term *term);

/*
**ft_split
*/
size_t	len_wd(char *str, char *charset);
size_t	count_malloc(char *s, char *str);
void		*ft_free(char **res, int j);
char			**ft_split(char *s, char *str);
size_t parse_command(size_t i, char *str, int *res, char *charset);

/*
**expander
*/
char **parse_first_arg(char **res, char **parsed_res);
char *expander(char *res, t_list *var_env, char **args, t_command *cmd);
char **parse_res(char **res, t_list *var_env, t_command *cmd);
char *handled_unset(char *res, t_list *var_env, t_command *cmd);
char *remove_antislashes(char *dest, char *str, t_list *var_env, t_command *cmd);

/*
**expander_utils
*/
void join_string_value(char **str, char **tmp, char *trim, int *index);
char *replace_by_env(char *trim, t_list *var_env, t_command *cmd);
char *non_handled_commands(char *res, t_list *var_env, t_command *cmd);
char *handled_export(char *res, t_list *var_env, t_command *cmd);
char *replace_by_env_value(char *trim, t_list *var_env, t_command *cmd);

/*
**expander_utils2
*/
char *get_env_name(int quotes, char *str_first);
char *search_env_name(char *str, t_list *var_env);
char *search_env_value(char *str, t_list *var_env);
char *antislashes_a_quotes(char *str);
char *antislashes_dolls(char *str);
int is_valid_env_c(char c);

/*
**expander_utils3
*/
char *get_string(char *str);
char *get_string_value(char *str);
char *get_env_value(char *str, t_list *var_env, t_command *cmd);
int even_or_odd(char *str);
char *find_op(char *str);

/*
**expander_utils4
*/
char *export_errors(char *str_first, char *str_secd, int quotes, char *res);
char *valid_export(char *str_first, char *str_secd, int quotes, char *res);
void env_quotes_a_values(char **str_first, char **str_secd, int *quotes);
void split_env_name_a_value(char **str_first, char **str_secd, char **p_bin, char *res);
void export_replace_by_env_value(char **str_first, char **str_secd,
t_list *var_env, t_command *cmd);

/*
**expander_utils5
*/
int strings_to_join(char **res, int i);
char **create_parsed_res(char **res, t_command *cmd);
char *parsed_res_error(char **parsed_res, int j, t_command *cmd);
char **last_command_rv(char **res, char **parsed_res);
void init_var_h_export(int *quotes, char **str_first, char **str_secd, char **name);

/*
**launch_exe
*/
int		launch_exe(char *exe, char *path, char **env, t_command *cmd);
void	find_exe(char *path, char **env, t_command *cmd);

/*
**launch_exe_utils
*/
char *ft_get_filename(const char *s, int c);
char *get_path(char *path, char c);
char **arg_tab(char *exe, char *path, char **env);
char **env_tab(char *path);

/*
**env
*/
void	set_env(char **tabl, t_list *var_env, t_command *cmd);
t_list	*set_new_env(char **env, t_list *var_env, t_command *cmd);
void	unset(t_list *env, char **tabl, t_command *cmd);
void	print_env(t_list *environ, t_command *cmd);
void	unset_cmd_path(int boolean, t_command *cmd);

/*
**env_utils
*/
char	*ft_get_name(char *str);
void	check_doublons_cl(char **tabl, char *i_name, char *j_name, int j);
t_list	*check_doublons(int k, int j, char **tabl, t_list *var_env);
void	replace_env(char *tabl, t_list *var_env);
void	add_to_env(char **tabl, int k, int l);

/*
**env_utils2
*/
char	**fill_list(t_list *environ, char **list, int i);
char	**sort_list(char **list, int i, int j);
void	print_sorted_env(t_list *environ, t_command *cmd);
int		is_valid_env_name(char *str);
int		is_valid_env_name_c(char c);

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
void    ft_cd(char **res, t_list *var_env, t_command *cmd);
void	free_cd(char *path, char *buf, char *old_pwd, char *ret);
int		if_too_many_args(char **res, t_command *cmd);
void	init_cd_strings(char **path, char **old_pwd, char **buf, char **ret);
void    ft_pwd(char **res, t_command *cmd);

/*
**path_utils
*/
int		count_back(char *str, int *j);
void	path_copy(char **buf, int m, int k);
void	cd_go_back(int *i, int k, char **buf, char *old_pwd);
int		cd_go_front(char *res, int *i, int k, char **buf);
void 	set_pwd_env(char *path, char *buf, t_list *var_env);

/*
**path_utils2
*/
char *cd_front_a_back(char *res, char *path, t_list *var_env, char *old_pwd);
char *get_cwd(void);
void	ft_cd_minus(char **res, t_list *var_env, t_command *cmd, char *old_pwd);
void	set_root_path(char **buf, char **path, char **res, char **str);
void	cd_failure(char **res, t_command *cmd, char *old_pwd, char *buf);

/*
**path_utils3
*/
void    cd_no_arg(t_list *var_env, t_command *cmd);

/*
**prep_line
*/
char *end_line(char *current, t_term *term);
char *get_char(char *current, t_term *term, char *buf);
char *go_line(t_term *term);
char *getcommand(char *str);

/*
**redir
*/
int		chrtabtab(char **res, char *str);
char	**divide_pipe(t_fd *f);
int		go_e(char **tabl, t_list *var_env, t_command *cmd);
int		go_instruction(char **tabl, t_list *var_env, t_command *cmd, char **env);
int		go_pipe(char **res, t_fd *f, t_list *var_env, t_command *cmd, char **env);
int		redir_and_send(t_fd *f, t_list *var_env, t_command *cmd, char **env);

/*
**redir_utils
*/
int		open_fds_out(char **res, int i, int m);
int		open_fds_in(char **res, int i);
int		handle_fds(char **res, t_fd *f);
int		count_pipes(char **res);
char	**end_redir(char **res, t_fd *f);

/*
**echo
*/
char	*echo_option(char *output, int option);
char	*get_echo_output(char *output, char **res, int i);
void	ft_echo(char **res, t_list *var_env);

/*
**exec
*/
int		set_args(char **res, char *path, t_command *cmd);
int		exec_command(char **args, char **res, char *path, int j);
char	**arguments(char **res, int i, char **args, char *path);
char	**environment(char *path);
int		exit_status(int status);

/*
**exec
*/
char	*get_location(char *arg);
char	*set_first_arg(char *p_bin, char *res);

/*
**exit
*/
int     ft_isdigit(int c);
void    ft_exit(char **res, t_command *cmd);

/*
**termcap
*/
char	**save_input(char *str, char **save);
void	restore_term(t_term *term);
void	get_cursor_pos(t_term *term, char **res);
void	get_cursor_space(t_term *term);
void	init_term(t_term *term);

/*
**termcap_arrow
*/
void	erase_line(int i, int j, t_term *term);
char	*handle_arrow_up(t_term *term, char *end);
char	*handle_arrow_down(t_term *term, char *end);
void	not_arrow(int i, char c, t_term *term);
char	*handle_arrow(t_term *term, char *end);

/*
**multipipe
*/
int	get_k(int k, char **res, int i, int j);
char **middle_pipe(char **res, int i);
void print_tabtab(char **res);
int handle_multipipes(t_fd *f, t_list *var_env, t_command *cmd, char **env);

/*
**parse_path
*/
char	**parse_path(char *s, char c);

/*
**sig_a_errors
*/
void	errors(t_command *cmd);
void	handle_signal(int code);

/*
**minishell_utils
*/
int		ft_strchr_bis(const char *s, int c);
int		check_word(char *str, char *to_find, int i);
int		search_word(char *str, char *to_find);
int		ft_isspace(char c);
int		is_handled_cmd(char *str);

/*
**minishell_utils2
*/
char	**copy_tabtab(char **res);
void	init_structs(t_command *cmd);
char	*cut_after_punct(char *dest, char *line, char *command);
int		count_tabs(char **res);
void	free_tabtab(char **res);

/*
**minishell_utils3
*/
int		is_symbol(char c, char comp);
int		count_pipes(char **res);
int		chrtabtab(char **res, char *str);
char	**replace_tabtab(char **tabl, int i, char *str);
void	erase_line(int i, int j, t_term *term);

/*
**gnl
*/
int		get_next_line(int fd, char **line);

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
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);

/*
**libft_utils2
*/
int		ft_strrchr(const char *s, int c);
void	*ft_calloc(size_t count, size_t size);
void	*ft_memcpy(void *dst, const void *src, size_t n);
void	*ft_memmove(void *dst, const void *src, size_t len);
int		ft_ischarset(char *str, char c);

/*
**libft_utils3
*/
void	ft_putstr_fd(char *s, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strtrim(char const *s1, char const *set);

/*
**libft_utils4
*/
int		ft_strlcpy(char *dst, const char *src, int dstsize);
int		ft_isalnum(int c);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_is_empty_string(char *str);
int	ft_putchar(int c);

/*
**libft_utils5
*/
int		ft_atoi(const char *str);
char	*rv_itoa(int n);

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
void	ft_record(void *lst, void *cmd);
void	ft_lstiter(t_list *lst, void (*f)(void *, void *), t_command *cmd);
void	ft_lstdel(t_list *lst);
int		record_cmd_path(void *lst, void *cmd);

extern t_sig g_sig;

#endif