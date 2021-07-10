#	ifndef MINISHELL_H
# define MINISHELL_H

# include <stddef.h>
# include <unistd.h>
# include <sys/types.h>
# include <dirent.h>
# include <stdio.h>
# include <errno.h>
# include <string.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <signal.h>
# include <curses.h>
# include <term.h>

# define BUFFER_SIZE 50

typedef struct s_sig
{
	int			sig;
	int			boolean;
	int			stop;
}				t_sig;

typedef struct s_list
{
	char			*name;
	void			*value;
	struct s_list	*prec;
	struct s_list	*next;
}				t_list;

typedef struct s_fd
{
	int			save_in;
	int			save_out;
	char		**save_pipe;
	char		**res;
	char		**first_res;
}				t_fd;

typedef struct s_mp
{
	int			fd[2];
	int			count;
	pid_t		pid;
	int			fdd;
	int			status;
	char		**first;
}				t_mp;

typedef struct s_term
{
	struct termios	s_termios;
	struct termios	s_termios_backup;
	int				x;
	int				y;
	int				col;
	int				lin;
	int				size;
	char			**done;
	char			*last;
	int				len;
	int				where;
	int				mtline;
}				t_term;

typedef struct s_command
{
	char		*path;
	int			index;
	int			cmd_rv;
	int			start;
	int			ret;
	int			bol;
	char		**res;
	char		**env;
}				t_command;

/*
**main_utils
*/
void	init_vars_main(char **line, char ***term_done, int ac, char *argv[]);
void	restore_fds(t_fd *f);
void	init_fds(t_fd *f);
void	set_env_list(t_list **var_env, char **env, t_command *cmd);

/*
**start_a_parse
*/
int		dispatch(char *str, char **env, t_list *var_env, t_command *cmd);
int		ft_is_fail_char(char *str);
void	main_loop(char *buf, char **env, t_list *var_env, t_command *cmd);
void	finish_line(t_command *cmd, t_term *term, t_list *var_env);

/*
**lexer
*/
size_t	parse_command(size_t i, char *str, int *res, char *charset);
size_t	len_wd(char *str, char *charset);
size_t	count_malloc(char *s, char *str);
void	init_vars_ft_split(size_t *i, size_t *j);
char	**ft_split(char *s, char *str);

/*
**lexer_utils
*/
int		is_not_charset(char *s, int j, char *str, int i);
void	*ft_free(char **res, int j);

/*
**expander
*/
char	*expander(char *res, t_list *var_env, char **args, t_command *cmd);
char	*remove_antislashes(char *dest);
void	init_vars_parse_res(int *i, int *j, char **str);
void	inc_j(char **parsed_res, int *j);
char	**parse_res(char **res, t_list *var_env, t_command *cmd);

/*
**expander_utils
*/
int		strings_to_join(char **res, int i);
char	**create_parsed_res(char **res);
char	*parsed_res_error(char *res, char *parsed_res, t_list *var_env, \
t_command *cmd);
char	**last_command_rv(char **res, char **parsed_res);
void	init_var_h_export(int *quotes, char **str_first, char **str_secd, \
char **name);

/*
**expander_utils2
*/
int		condition_dq(int i, int len, char *str);
int		condition_sq(int i, int len, char *str);
void	init_vars_get_env_v(int *i, char **ret);
int		condition_one(int i, char *dest, char *str, char *env);
int		is_escaped_char(int i, char *dest);

/*
**expander_utils3
*/
char	*trim_dq(int *bool2, char *tmp);
char	*trim_sq(int *boolean, char *tmp_sub);
void	init_var_nh_cmd(int *boolean, int *index, int *bool2, int *cmd_bol);
void	trim_s_quotes(char **buf, char *tmp_sub, int bool2, char *tmp);
char	*no_trim_starting_space(char *tmp, t_list *var_env, t_command *cmd);

/*
**expander_utils4
*/
char    *ft_free_3_strings_a_return(char *str_first, char *str_secd, char *str_third);

/*
**expander_a_env
*/
char	*replace_by_env_value_no_space(char *trim, t_list *var_env, \
t_command *cmd);
char	*replace_by_env_value(char *trim, t_list *var_env, t_command *cmd);
char	*non_handled_commands(char *res, t_list *var_env, t_command *cmd);
char	*handled_export(char *res, t_list *var_env, t_command *cmd);

/*
**unset
*/

void	remove_empty_string(char *str, int *j);
char	*write_error(char *str, t_command *cmd);
void	if_d_quotes_unset(char **trim, char *res, int *quotes);
void	if_s_quotes_unset(char *trim, char **trim2);
char	*handled_unset(char *res, t_list *var_env, t_command *cmd);

/*
**export
*/
void	free_export_errors(char *s1, char *s2, char *s3, char *s4);
void	if_s_quotes(char *str_first, char *str_secd, char **str_f, \
char **str_s);
char	*export_errors(char *str_first, char *str_secd, char *res);
void	ft_free_2_strings(char *s1, char *s2);
char	*valid_export(char *str_first, char *str_secd, char *res);

/*
**export_utils
*/
void	if_d_quotes(char *str_first, char *str_secd, char **str_f, \
char **str_s);
void	env_quotes_a_values(char **str_first, char **str_secd, \
int *quotes, char **name);
void	which_is_name_a_value(char **str_first, char **str_secd, char **p_bin, \
char *res);
void	split_env_name_a_value(char **str_first, char **str_secd, \
char **p_bin, char *res);
void	export_replace_by_env_value(char **str_first, char **str_secd, \
t_list *var_env, t_command *cmd);

/*
**env_values
*/
void	join_string_value(char **str, char **tmp, char *trim, int *index);
void	init_vars_replace_by_env(size_t *i, char **tmp, char **str);
int		is_not_env_value(size_t i, char *trim);
char	*remove_starting_spaces(char *str);
char	*is_it_unknown_var(char *tmp);
int		is_in_sq_string(int i, char *str);
int		is_in_dq_string(int i, char *str);

/*
**env_values_utils
*/
int		is_valid_env_c(char c);
void	fill_string_dq(int *i, int *j, char *str, char **ret);
void	fill_string_sq(int *i, int *j, char *str, char **ret);
void	fill_string(int *i, int *j, char *str, char **ret);
void	init_vars_a_a_q(int *i, int *j);

/*
**env_values_utils2
*/
char	*get_string(char *str);
char	*get_string_value(char *str, int boolean, char *trim, int x);
char	*get_env_value(char *str, t_list *var_env, t_command *cmd);
int		even_or_odd(char *str);
char	*find_op(char *str);
int		is_command_return_value(int i, char *buf);

/*
**env_values_utils3
*/
char	*search_env_name(char *str, t_list *var_env);
char	*search_env_value(char *str, t_list *var_env);
char	*antislashes_dolls(char *str);
char	*antislashes_a_quotes(char *str);
char	*get_env_name(int quotes, char *str_first);

/*
**launch_exe
*/
void	init_vars_launch_exe(pid_t *pid, int *ret, int *status);
void	free_2_tabs(char **argv, char **envp);
int		launch_exe(char *path, char **env, t_command *cmd);
void	find_exe(char *path, char **env, t_command *cmd);
int		exit_code_launch_exe(int status);

/*
**launch_exe_utils
*/
char	*ft_get_filename(const char *s, int c);
char	*get_path(char *path, char c);
char	**arg_tab(char *path, char **env);
char	**env_tab(char *path);
void	write_error_launch_exe(char *path);

/*
**launch_exe_utils2
*/
void	opendir_error(char *path, t_command *cmd, char *str, \
char *path_mod);
void	init_vars_find_exe(char **str, char **path_mod, char *path, \
DIR **dir);
void	launch_exe_error(char *path, char **env, t_command *cmd);
void	child_process(char **argv, char **envp, char *path, int *ret);

/*
**env
*/
t_list	*set_new_env(char **env, t_list *var_env, t_command *cmd);
void	reset_cmd_path(t_list *lst, t_command *cmd);
void	set_env(char **tabl, t_list *var_env, t_command *cmd, int j);
void	unset(t_list *env, char **tabl, t_command *cmd, int j);
void	print_env(t_list *environ, t_command *cmd);

/*
**env_utils
*/
char	*ft_get_name(char *str);
void	add_to_env(char **tabl, int k, int l);
void	check_doublons_cl(char **tabl, char *i_name, char *j_name, int j);
t_list	*check_doublons(int k, int j, char **tabl, t_list *var_env);
void	replace_env(char *tabl, t_list *var_env);

/*
**env_utils2
*/
void	init_vars_fill_list(int *i, t_list **environ, t_list **tmp);
char	**fill_list(t_list *environ, char **list, int i);
char	**sort_list(char **list, int i, int j);
void	print_sorted_env(t_list *environ, t_command *cmd);
int		is_valid_env_name(char *str);

/*
**env_utils3
*/
char	*create_i_value(char *tab_k, char *i_value);
char	*create_j_value(char *tab_l, char *j_value);
void	add_to_env_l(char **tabl, char *j_name, int k, int l);
void	add_to_env_k(char **tabl, char *i_name, int k, int l);
void	set_i_a_j_name(char **i_name, char **j_name, char **split, \
char **split2);

/*
**env_utils4
*/
void	unset_cmd_path(int boolean, t_command *cmd);
void	name_a_value_var(char **name, char **value, char **env, int k);
void	init_strings_set_env(t_list **tmp_new, t_list **tmp, char **name);
void	init_vars_unset(char **name, int *i, int *boolean);

/*
**env_utils5
*/
void	init_i_a_j_values(char **i_value, char **j_value, char *tabl_k,
			char *tabl_l);
void	plus_equal(char **tabl, char *x_name, char *a_value, char *b_value);
void	equal(char **tabl, char *x_name, char *a_value, char *b_value);

/*
**path
*/
int		if_too_many_args(char **res, t_command *cmd);
void	init_cd_strings(char **buf, char **ret, char *path);
void	init_2_strings(char **path, char **str);
void	set_current_path_cd(char **str, char **path, t_list *var_env);
void	ft_cd(char **res, t_list *var_env, t_command *cmd);

/*
**path_utils
*/
int		count_back(char *str, int *j);
void	path_copy(char **buf, int k);
int		count_slash(char *old_pwd);
void	cd_go_back(int k, char **buf, char *old_pwd);
void	cd_go_front(char *res, int *i, char **buf);

/*
**path_utils2
*/
char	*cd_front_a_back(char *res, char *path, char *old_pwd);
char	*get_cwd(void);
void	ft_cd_minus(char **res, t_list *var_env, t_command *cmd, char *old_pwd);
void	set_root_path(char **buf, char **res);
void	cd_failure(char **res, t_command *cmd, char *old_pwd);

/*
**path_utils3
*/
void	cd_no_arg(t_list *var_env, t_command *cmd);
void	set_pwd_env(char *path, char *buf, t_list *var_env);
void	write_cd_option_error(char *res, t_command *cmd, char **str, \
t_list *var_env);
void	write_cd_minus_option(char **str, t_list *var_env);
void	ft_pwd(t_command *cmd, t_list *var_env);

/*
**prep_line
*/
char	*end_line(char *current, t_term *term);
char	*get_char(char *current, t_term *term, char *buf);
char	*go_line(t_term *term);
char	*getcommand(char *str);

/*
**redir
*/
int		chrtabtab(char **res, char *str);
char	**divide_pipe(t_fd *f);
int		go_e(char **tabl, t_list *var_env, t_command *cmd, int j);
int		go_instruction(char **tabl, t_list *var_env, t_command *cmd, \
char **env);
int		redir_and_send(t_fd *f, t_list *var_env, t_command *cmd, \
char **env);

/*
**redir_utils
*/
int		open_fds_out(char **res, int i, int m);
int		open_fds_in(char **res, int i);
int		handle_fds(char **res);
int		count_pipes(char **res);
char	**end_redir(char **res, t_fd *f);
char	**end_redir_pipe(char **res, t_fd *f);

/*
**redir_utils2
*/

int		check_valid_res_bis(char **str);
int		check_valid_res(char **str);
char	**divide_pipe(t_fd *f);
int		go_pipe(t_fd *f, t_list *var_env, t_command *cmd, char **env);

/*
**redir_utils3
*/
char	**failed_fd(t_fd *f, char **res);
char	**middle_pipe(char **res, int i);
int		end_pipe(t_fd *f, t_mp *mp);
char	**get_redir_ready(char **res);

/*
**echo
*/
char	*echo_option(char *output, int option);
char	*get_echo_output(char *output, char **res, int i);
void	ft_echo(char **res, t_command *cmd);

/*
**exec
*/
int		exit_status(int status);
int		test_shell_bin(char **tabl, char **p_bin, char **res, char **env);
int		exec_command(char **args, char **res, t_command *cmd, int j);
void	set_args(char **res, t_command *cmd, int i);
void	init_vars_exec(int *status, char ***env, t_command *cmd, char ***p_bin);

/*
**exec_utils
*/
char	*get_location(char *arg);
char	*set_first_arg(char *p_bin, char *res);
char	**arguments(char **res, int j, char **args, char *path);
char	**environment(char *path);
void	write_error_shell(t_command *cmd, char **res);

/*
**exec_utils2
*/
void	ft_free_set_args(char **args, char **n_res);
void	init_vars_set_args(int *index, int *k, char ***n_res, char **res);
void	init_2_vars(int *i, int *k);
int		command_not_found(char **tabl, char **env, char **p_bin);
int		command_found(char **tabl, char **env, char **p_bin);

/*
**exec_utils3
*/
void	split_execve_args(char ***new_res, char **tmp, int *x, int *j);
void	init_vars_new_res(int *i, int *j, int *x, char ***tmp);
char	**new_res(char **res);

/*
**exit
*/
int		ft_isdigit(int c);
void	exit_error_no_nb(char **res, t_command *cmd);
void	exit_too_many_args(t_command *cmd);
void	exit_code(char **res, t_command *cmd);
void	ft_exit(int i, char **res, t_command *cmd);

/*
**termcap
*/
char	**save_input(char *str, char **save);
void	restore_term(t_term *term);
void	get_cursor_pos(t_term *term, char **res);
void	get_cursor_space(t_term *term);
void	init_term(t_term *term);

/*
**termcap_utils
*/
char	*handle_delete(char *current, t_term *term);
void	handle_ctrl_d(char *current, t_term *term);
char	*handle_hist(t_term *term, char *end);

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
int		get_k(int k, char **res, int i, int j);
char	**middle_pipe(char **res, int i);
void	print_tabtab(char **res);
void	init_mp(t_mp *mp, int i, t_fd *f);
int		handle_multipipes(t_fd *f, t_list *var_env, t_command *cmd, char **env);

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
int		is_handled_cmd(char *str);
int		ft_strchr_bis(const char *s, int c);
int		ft_isspace(char c);
int		check_word(char *str, char *to_find, int i);
int		search_word(char *str, char *to_find);

/*
**minishell_utils2
*/
void	init_4_values(int *s_q, int *d_q, int *s_q2, int *d_q2);
int		is_in_string(char *line, int index);
char	*cut_after_punct(char *dest, char *line, char *command);
char	**copy_tabtab(char **res);
int		is_string(char *str, char *dest, int i);

/*
**minishell_utils3
*/
int		is_symbol(char c, char comp);
int		count_pipes(char **res);
int		chrtabtab(char **res, char *str);
char	**replace_tabtab(char **tabl, int i, char *str);
void	erase_line(int i, int j, t_term *term);

/*
**minishell_utils4
*/
void	free_string(char *str);
void	if_string_literal(char **tmp, char **tmp2);
void	if_dq_unkwn_var(char **tmp, char *str, int *boolean);
int		is_unknown_env_variable(char *str, t_list *var_env, t_command *cmd);

/*
**minishell_utils5
*/
int		count_tabs(char **res);
void	free_tabtab(char **res);
void	init_structs(t_command *cmd);
void	free_cd(char *path, char *buf, char *old_pwd, char *ret);
char	**put_list_in_tab(t_list *var_env);

/*
**minishell_utils6
*/
char	*free_null(char *str);
int		handle_j_down(t_term *term);

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
int		ft_strcmp_no_slash(const char *s1, const char *s2);

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
int		ft_isalnum(int c);
int		ft_strlcpy(char *dst, const char *src, int dstsize);
char	*ft_strjoin_free(char *s1, char *s2);
int		ft_is_empty_string(char *str);
int		ft_putchar(int c);

/*
**libft_utils5
*/
int		ft_atoi(const char *str);
char	*rv_itoa(int n, char *buf);

/*
**libft_utils6
*/
void	ft_putstr_nbr(int i, int fd);
char	*ft_itoa(int n);

/*
**libft_utils7
*/
char	*ft_strnstr(const char *haystack, const char *needle, size_t len);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
int		faulty_redir(t_command *cmd);
void	control_fds(t_mp *mp, int i);

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
int		record_cmd_path(void *lst, void *cmd);
void	ft_lstiter(t_list *lst, void (*f)(void *, void *), \
t_command *cmd);
void	ft_lstdel(t_list *lst);

extern t_sig	g_sig;

#endif