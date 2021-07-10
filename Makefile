SRCS =	./srcs/echo.c\
	./srcs/env_utils.c\
	./srcs/env_utils2.c\
	./srcs/env_utils3.c\
	./srcs/env_utils4.c\
	./srcs/env_utils5.c\
	./srcs/env_values.c\
	./srcs/env_values_utils.c\
	./srcs/env_values_utils2.c\
	./srcs/env_values_utils3.c\
	./srcs/env.c\
	./srcs/exec.c\
	./srcs/exec_utils.c\
	./srcs/exec_utils2.c\
	./srcs/exec_utils3.c\
	./srcs/exit.c\
	./srcs/expander_a_env.c\
	./srcs/expander_utils.c\
	./srcs/expander_utils2.c\
	./srcs/expander_utils3.c\
	./srcs/expander_utils4.c\
	./srcs/expander.c\
	./srcs/export_utils.c\
	./srcs/export.c\
	./srcs/gnl_utils.c\
	./srcs/launch_exe_utils.c\
	./srcs/launch_exe_utils2.c\
	./srcs/launch_exe.c\
	./srcs/lexer_utils.c\
	./srcs/lexer.c\
	./srcs/libft_list.c\
	./srcs/libft_list2.c\
	./srcs/libft_list3.c\
	./srcs/libft_utils.c\
	./srcs/libft_utils2.c\
	./srcs/libft_utils3.c\
	./srcs/libft_utils4.c\
	./srcs/libft_utils5.c\
	./srcs/libft_utils6.c\
	./srcs/libft_utils7.c\
	./srcs/main_utils.c\
	./srcs/minishell_utils.c\
	./srcs/minishell_utils2.c\
	./srcs/multipipe.c\
	./srcs/multipipe_utils.c\
	./srcs/minishell_utils3.c\
	./srcs/minishell_utils4.c\
	./srcs/minishell_utils5.c\
	./srcs/minishell_utils6.c\
	./srcs/parse_path.c\
	./srcs/path.c\
	./srcs/path_utils.c\
	./srcs/path_utils2.c\
	./srcs/path_utils3.c\
	./srcs/prep_line.c\
	./srcs/redir.c\
	./srcs/redir_utils.c\
	./srcs/redir_utils2.c\
	./srcs/redir_utils3.c\
	./srcs/sig_a_errors.c\
	./srcs/start_a_parse.c\
	./srcs/termcap.c\
	./srcs/termcap_utils.c\
	./srcs/termcap_arrow.c\
	./srcs/unset.c\

RENAME		= mv a.out minishell
OBJ			= $(SRCS:.c=.o)
NAME		= minishell
FS			= a.out.dSYM minishell.dSYM
CC			= gcc
RM			= rm -f
RM_DIR		= rm -rf
CFLAGS		= -g3 -fsanitize=address -Wall -Wextra -Werror
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

