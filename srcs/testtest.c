#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <term.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>
size_t	ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
int	ft_strcmp(const char *s1, const char *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *s1);
void	ft_putstr_fd(char *s, int fd);



int main(void)
{
    char *line;
    char *buf1;
    char buf[2];
    int quit;

    line = NULL;
    quit = 0;
    while (quit == 0)
    {
        if ((int)buf[0] == 4)
            out(1);
        else if (buf[0] == '\n')
        {
            quit = 1;
        }
        else
        {
            if (line == NULL)
                line = ft_strdup(buf);
            else
                buf1 = ft_strdup(line);
                free(line);
                line = ft_strjoin(buf1, buf);
                free(buf1);
        }
    }
}