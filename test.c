#include <stdlib.h>
#include <unistd.h>

#include <curses.h>
#include <term.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int test_ft(int c)
{
    write(1, "ok", 2);
    return (0);
}

int main(int argc, char **argv)
{
    int ret;
     struct termios s_termios;
     struct termios s_termios_backup;
    char *term_type = getenv("TERM");

    ret = tgetent(NULL, term_type);

    char *arr_u;
    char *arr_d;
    s_termios.c_lflag &= ~(ICANON); /* Met le terminal en mode non canonique. La fonction read recevra les entrées clavier en direct sans attendre qu'on appuie sur Enter */
    if (tcsetattr(0, 0, &s_termios) == -1)
          return (-1);
    // // s_termios.c_lflag &= ~(ECHO);
    int i = 0;
    char *cl_cap = tgetstr("up", NULL);
    char *cl_cap1 = tgetstr("do", NULL);
    while (i != 10)
    {
    //     write(1, "ok", 2);
        char buf[64];
        wait(2);
        read(0, buf, 64);
        // buf[4] = '\0';
        int j = 0;
        if (strcmp(buf, cl_cap) == 0)
            write(1, "yes", 3);
        // while (buf[j])
        //     {write(1, &buf[j], 1);
        //     j++;}
    //     printf("%s", buf);
    //     write(1, "ok", 2);
        // if (buf == tgetstr("do", NULL))
        // {
        //     write(1, "down", 4);
            i++;
        // }
    }

 if (tcsetattr(0, 0, &s_termios_backup) == -1)
          return (-1);
    
    // tputs (cl_cap, 1, test_ft);


    // tputs (cl_cap1, 1, test_ft);

    /* On évite les warnings pour variables non utilisées. */
    (void)argc;
    (void)argv;

    return ret;
}