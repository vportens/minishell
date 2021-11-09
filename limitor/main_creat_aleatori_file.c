#include "minishell.h"

int aleatori_char(void)
{
	char	buff[4];
	int		nbr;
	int		fd;

	fd = open("/dev/random", O_RDONLY);
	if (fd < -1)
		return (-1);
	read(fd, buff, 4);
	nbr = *(int *)buff;
	if (nbr < 0)
		nbr++;
	if (nbr < 0)
		nbr = nbr * (-1);
	return ('a' + nbr % 26);	
}

char	*creat_aleatori_name()
{
	char	*name_file;
	int		i;

	i = 0;
	name_file = malloc(sizeof(char) * 11);
	name_file[10] = '\0';
	while (i < 10)
	{
		name_file[i] = (char)aleatori_char();
		i++;
	}
	return (name_file);
}

int	main(int ac, char **av, char **envp)
{
	char	*name_file;
	int		fd;
	char	*str;
	pid_t	pid;
	char	*argv[2] = {"/bin/cat", NULL};

	name_file = NULL;
	fd = -1;
	if (ac < 2)
	{
		write(1, "need arg\n", ft_strlen("need arg\n"));
		return (1);
	}
	pid = fork();
	if (pid == 0)
	{
		while (fd == -1)
		{
			if (name_file)
				free(name_file);
			name_file = creat_aleatori_name();
			fd = open(name_file, O_CREAT | O_EXCL | O_RDWR, 0644);
		}
		while (1)
		{
			str = readline(">");
			if (str == NULL)
				return (1);
			if (ft_strcmp(av[1], str) == 1)
				break ;
			write(fd, str, ft_strlen(str));
			write(fd, "\n", 1);
			free(str);
		}
		dup2(fd, STDIN_FILENO);
		dup2(1, STDOUT_FILENO);
	//	close(fd);
	//	unlink(name_file);
		printf("argv[0] : %s\n", argv[0]);
		execve(argv[0], argv,envp);
		printf("je passe pas par execve\n");
		exit(1);
	}
	waitpid(pid, NULL, 0);
//	printf("fd : %d\n", fd);

}
