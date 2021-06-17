SRCS =	./debug_to_delete.c\
	./echo.c\
	./env_utils.c\
	./env_utils2.c\
	./env_utils3.c\
	./env_utils4.c\
	./env_values.c\
	./env_values_utils.c\
	./env_values_utils2.c\
	./env_values_utils3.c\
	./env.c\
	./exec.c\
	./exec_utils.c\
	./exec_utils2.c\
	./exit.c\
	./expander_a_env.c\
	./expander_utils.c\
	./expander_utils2.c\
	./expander_utils3.c\
	./expander.c\
	./export_utils.c\
	./export.c\
	./gnl.c\
	./gnl_utils.c\
	./launch_exe_utils.c\
	./launch_exe_utils2.c\
	./launch_exe.c\
	./lexer_utils.c\
	./lexer.c\
	./libft_list.c\
	./libft_list2.c\
	./libft_utils.c\
	./libft_utils2.c\
	./libft_utils3.c\
	./libft_utils4.c\
	./libft_utils5.c\
	./libft_utils6.c\
	./minishell_utils.c\
	./minishell_utils2.c\
	./multipipe.c\
	./minishell_utils3.c\
	./minishell_utils4.c\
	./minishell_utils5.c\
	./parse_path.c\
	./path.c\
	./path_utils.c\
	./path_utils2.c\
	./path_utils3.c\
	./prep_line.c\
	./redir.c\
	./redir_utils.c\
	./redir_utils2.c\
	./sig_a_errors.c\
	./start_a_parse.c\
	./termcap.c\
	./termcap_utils.c\
	./termcap_arrow.c\
	./unset.c\

RENAME		= mv a.out minishell
OBJ			= $(SRCS:.c=.o)
NAME		= minishell
FS			= a.out.dSYM minishell.dSYM valgrind_log
CC			= gcc
RM			= rm -f
RM_DIR		= rm -rf
CFLAGS		= -g3 -fsanitize=address #-Wall -Wextra -Werror
DEP			= -lncurses
$(NAME):		$(OBJ)
#add CFLAGS
				@$(CC) $(CFLAGS) $(SRCS) $(DEP)
				@$(RENAME)
all:			$(NAME)
clean:
				@$(RM) $(OBJ)
fclean:			clean
				@$(RM) $(NAME)
				@$(RM_DIR) $(FS)
re:				fclean all	
.PHONY:			all clean fclean re

