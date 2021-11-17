#include "minishell.h"
#include "signal.h"
#include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

void    print(void);

void    sig_test(int sig)
{

    printf("signal num : %d\n", sig);
    if (sig == 2)
    {
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();

    }
    if (sig == 3)
        exit(1);

}

void    print(void)
{
    char    *str;
    int     pid;
    int     i;

    i = 0;
    while (1)
    {
        str = readline(">");

        if (str != NULL)
        {
            signal(SIGINT, SIG_IGN);
            signal(SIGQUIT, SIG_IGN);
            pid = fork();
            if (pid == 0)
            {
                signal(SIGQUIT, SIG_DFL);
                signal(SIGINT, SIG_DFL);
                while (1)
                {
                    i++;
                    if (i % 100 == 99)
                        i = 0;
                    if (str == NULL)
                        break;

                }
            }
            else
            {
                waitpid(pid, NULL, 0);
                signal(SIGINT, sig_test);
                signal(SIGQUIT, sig_test);

            }
            write(1, str, ft_strlen(str));
            write(1, "\n", 1);

        }
        if (str == NULL)
            exit(1);


    }

}



int main(int ac, char **av)
{

    signal(SIGINT, sig_test);   
    signal(SIGQUIT, sig_test);

    print();
}