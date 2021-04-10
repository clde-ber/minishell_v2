SRCS =	./debug_to_delete.c\
	./echo.c\
	./env_utils.c\
	./env_utils2.c\
	./env.c\
	./exec.c\
	./expander_utils.c\
	./expander_utils2.c\
	./expander.c\
	./ft_split.c\
	./gnl_utils.c\
	./gnl.c\
	./launch_exe_utils.c\
	./launch_exe.c\
	./libft_list.c\
	./libft_list2.c\
	./libft_utils.c\
	./libft_utils2.c\
	./libft_utils3.c\
	./libft_utils4.c\
	./minishell_utils.c\
	./minishell_utils2.c\
	./parse_path.c\
	./path.c\
	./redir.c\
	./sig_a_errors.c\
	./start_a_parse_bulle.c\

RENAME		= mv a.out minishell
OBJ			= $(SRCS:.c=.o)
NAME		= minishell
FS		= a.out.dSYM minishell.dSYM valgrind_log
CC			= gcc
RM			= rm -f
RM_DIR		= rm -rf
CFLAGS		= -g3 -fsanitize=address #-Wall -Wextra -Werror
$(NAME):		$(OBJ)
#add CFLAGS
				@$(CC) $(CFLAGS) $(SRCS)
				@$(RENAME)
all:			$(NAME)
clean:
				@$(RM) $(OBJ)
fclean:			clean
				@$(RM) $(NAME)
				@$(RM_DIR) $(FS)
re:				fclean all	
.PHONY:			all clean fclean re
