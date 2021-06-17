#include <stdlib.h>
#include <unistd.h>

#include <curses.h>
#include <term.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

// int test_ft(int c)
// {
//     write(1, "ok", 2);
//     return (0);
// }

//maybe pass term in noncanon, get char, check char if arrow
//if not: save it
//if it is, display line and change cursor 

void ft_putchar(int c)
{
    write(1, &c, 1);
}

int main(int argc, char **argv)
{
    int ret;
     struct termios s_termios;
     struct termios s_termios_backup;
    char *term_type = getenv("TERM");
    int col;
    int line;

    tgetent(NULL, getenv("TERM"));
	tcgetattr(STDOUT_FILENO, &s_termios);
	tcgetattr(STDOUT_FILENO, &s_termios_backup);
	s_termios.c_lflag &= ~(ICANON | ECHO);
	s_termios.c_cc[VTIME] = 0;
	s_termios.c_cc[VMIN] = 1;
	col = tgetnum("co");
	line = tgetnum("li");
	tputs(tgetstr("cl", NULL), 1, ft_putchar);
	// if (init_info(envp))
	// 	exit(EXIT_FAILURE);
	tcsetattr(STDOUT_FILENO, TCSANOW, &s_termios);
    
    int		first;
	char	*cur_dir;

	first = 1;
	ft_printf(RED "Welcome to Minisheh\n" RESET);
	while (!g_info->crashed)
	{
        //current path
		cur_dir = get_cur_dir();
		if (!(cur_dir))
			cur_dir = ft_strdup("/");
		ft_printf(BLUE "~ %s > " RESET, cur_dir);
		//position curseur terminal
        get_pos(&g_info->cursor.start_posx, &g_info->cursor.start_posy);
		g_info->prompt_len = ft_strlen(cur_dir) + 6;
		g_info->cmd_head = ft_create_elem(create_cmd_struct());
		process_line(first);
		first = 0;
		update_cmd_status();
		reset_info();
		remove_useless_history();
		secure_free(cur_dir);
	}
	free_blocks(g_info->block_head);
	free_tab(&g_info->dir_paths);
	secure_free(g_info->line);
	ft_list_clear(g_info->env_head, free_env_struct);
	ft_list_clear(g_info->history_head, free_history_struct);
	secure_free(g_info);
	return (SUCCESS);
}

//     ret = tgetent(NULL, term_type);

//     char *arr_u;
//     char *arr_d;
//     s_termios.c_lflag &= ~(ICANON); /* Met le terminal en mode non canonique. La fonction read recevra les entrées clavier en direct sans attendre qu'on appuie sur Enter */
//     if (tcsetattr(0, 0, &s_termios) == -1)
//           return (-1);
//     // // s_termios.c_lflag &= ~(ECHO);
//     int i = 0;
//     char *cl_cap = tgetstr("up", NULL);
//     char *cl_cap1 = tgetstr("do", NULL);
//     while (i != 10)
//     {
//     //     write(1, "ok", 2);
//         char buf[64];
//         wait(2);
//         read(0, buf, 64);
//         // buf[4] = '\0';
//         int j = 0;
//         if (strcmp(buf, cl_cap) == 0)
//             write(1, "yes", 3);
//         // while (buf[j])
//         //     {write(1, &buf[j], 1);
//         //     j++;}
//     //     printf("%s", buf);
//     //     write(1, "ok", 2);
//         // if (buf == tgetstr("do", NULL))
//         // {
//         //     write(1, "down", 4);
//             i++;
//         // }
//     }

//  if (tcsetattr(0, 0, &s_termios_backup) == -1)
//           return (-1);
    
//     // tputs (cl_cap, 1, test_ft);


//     // tputs (cl_cap1, 1, test_ft);

//     /* On évite les warnings pour variables non utilisées. */
//     (void)argc;
//     (void)argv;

//     return ret;
// }