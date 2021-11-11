#include "minishell.h"
#include "signal.h"
#include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

int	g_status;
char	*str;

void	print(void);

void	print(void)
{
	char	*str;

	while (1)
	{
		str = readline(">");
		if (str != NULL)
		{
			write(1, str, ft_strlen(str));
			write(1, "\n", 1);
		}
	}

}

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		if (g_status == 0) // not in fork
		{
			//free_all;
			// free str
			// return str == NULL
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
     	   rl_redisplay();
			printf("modif str status to null\n");
			return ;

		}
		else 
		{
			exit(1);
		}
		printf("salut les amiches\n");
	}
	else if (sig == SIGQUIT)
	{
		printf("le caca c'est pas tres bon\n");
		exit(1);
	}

}


int	main(int ac, char **av)
{
	struct sigaction stc;

	str = NULL;
	g_status = 0;
	stc.sa_handler = signal_handler;
	stc.sa_flags = 0;
	sigaction(SIGINT, &stc, NULL);
	sigaction(SIGQUIT, &stc, NULL);
	print();
}
