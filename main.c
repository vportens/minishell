/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 08:58:02 by laclide           #+#    #+#             */
/*   Updated: 2021/11/21 19:53:48 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	exit_status;

int	free_all(t_commande_line **cmd_line)
{
	t_commande_line *tmp;
	t_token			*tok;
	int				i;

	if (cmd_line)
	{
//	printf("cmdl exist\n");
	while (*cmd_line)
	{
//		printf("je rentre dans cmdl\n");
		tmp = (*cmd_line)->next;
		if ((*cmd_line)->string)
			free((*cmd_line)->string);
		
//		printf("je free string\n");
		if ((*cmd_line)->argv)
			free((*cmd_line)->argv);
//		printf("je free argvl\n");
		if ((*cmd_line)->first_token)
		{
			
//			printf("je rentre dans token\n");
			i = 0;	
			while ((*cmd_line)->first_token)
			{ 
//				printf("token %d\n", i);
//				printf("token str %s\n",(*cmd_line)->first_token->str);

				tok = (*cmd_line)->first_token->next;
				if ((*cmd_line)->first_token->str)
					free((*cmd_line)->first_token->str);
//				printf("str de tok free\n");

				free((*cmd_line)->first_token);
//				printf("tok free\n");
				(*cmd_line)->first_token = tok;
				i++;
			}
//			printf("je sort dans token\n");
		}
		if ((*cmd_line)->name_file)
			free((*cmd_line)->name_file);
//		printf("je free cmdl\n");
		free((*cmd_line));
		*cmd_line = tmp;
	}
	}
	return (1);
}

int	pars(char *str, t_commande_line **cmd_line)
{
	int	res;

	res = unclose_quote(str);
//	printf("sort de unclose_quote\n");
	if (res > 0)
	{
		free_all(cmd_line);
	}
	else
	{
		if (get_cmd_line(str, cmd_line) > 0)		/* ici on malloc et remplit cmd_line->string*/
		{
			free_all(cmd_line);
			free(str);
			return (50); // clean all arg;
		}
//		printf("sort de get_cmd_line\n");
		
		if (split_all_cmdl_string_to_token(cmd_line) > 0) /* ici on malloc les token et on remplit token->str et init token->type*/
		{
			free_all(cmd_line);
			free(str);
			return (50); // clean all arg
		}
//		printf("sort de splitall\n");
		
		res = expend_words(cmd_line);
		if (res != 0)
		{
			free_all(cmd_line);
			if (res == 50)
			{
				free(str);
				return (50);
			}
		}
//		printf("sort de expend_word\n");
		
		if (organise_arg(cmd_line) != 0)
		{
			free_all(cmd_line);
			free(str);
			return (50);
		}
//		printf("sort de orga\n");
		
	}
	return (res);
}

void	print_cmdl(t_commande_line **cmdl)
{
	t_commande_line *cur_b;
	t_token			*cur_t;
	int				i;
	int				j;

	i = 0;
	j = 0;
	cur_b = *cmdl;
	while (cur_b)
	{
		printf("cmd_line n %d to exec: %s\\n\n", j, cur_b->string);
		cur_t = cur_b->first_token;
		while (cur_t)
		{
			printf("	word : %s\\n\n", cur_t->str);
			printf("	type : ");
			if (cur_t->type == 0)
				printf("NONE\n");
			if (cur_t->type == 1)
				printf("ARG\n");
			if (cur_t->type == 2)
				printf("BUILTIN\n");
			if (cur_t->type == 3)
				printf("OPEN_FILE\n");
			if (cur_t->type == 4)
				printf("HERE_DOC\n");
			if (cur_t->type == 5)
				printf("LIMITOR\n");
			if (cur_t->type == 6)
				printf("CREAT_FILE\n");
			if (cur_t->type == 7)
				printf("WRITE_FILE\n");
			if (cur_t->type == 8)
				printf("FILE_IN\n");
			if (cur_t->type == 9)
				printf("FILE_OUT\n");
			if (cur_t->type == 10)
				printf("FILE_OUT_OVER\n");
			if (cur_t->expanded == 0)
				printf("	expanded : FALSE\n");
			if (cur_t->expanded == 1)
				printf("	expanded : TRUE\n");
			printf("\n");
			cur_t = cur_t->next;  
		}
		i = 0;
		while (cur_b->argv[i])
		{
			printf("	argv[%d] : %s\n", i, cur_b->argv[i]);
			i++;
		}
		cur_b = cur_b->next;
		j++;
	}
}

void	signal_cmd(int sig)
{
	exit_status += sig;
	if (sig == 2)
	{
		exit_status = 130;
        printf("\n");
        rl_on_new_line();
        rl_replace_line("", 0);
        rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(2 ,"Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
		exit (1);
	}
}

int	check_str(char *str)
{
	int	i;
	int	dif;

	i = 0;
	dif = 0;
	while (str[i])
	{
		if (str[i] != ' ' && str[i] != '|')
			dif = 1;
		if (str[i] == '|')
		{
			if (dif == 0)
				return (1);
			dif = 0;
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	char			*str;
	int				res;
	t_commande_line	*cmd_line;
	
	cmd_line = NULL;
	exit_status = 0;
	ft_init_t_env(envp);
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, SIG_IGN);
	if (ac && av)
	{
	while (1)
	{
		str = readline("minishell$> ");
		add_history(str);
		signal(SIGINT, signal_cmd);
		signal(SIGQUIT, SIG_IGN);
		if (str == NULL)
		{
			printf("exit\n");
			ft_clean_env();
			return (free_all(&cmd_line));

		}
		if (check_str(str) != 0)
			write(2, "minishell: syntax error near unexpected token '|' \n", ft_strlen("minishell: syntax error near unexpected token '|' \n"));
		else
		{
//		printf("on rentre dans pars\n");
		res = pars(str, &cmd_line);
//		printf("on sort de pars");
		if (res == 50)
		{
			free(str);
			free_all(&cmd_line);
			ft_clean_env();
			write(1, "malloc error\n", 13);
			return (50);
		}
		if (res == 0)
		{
		//	print_cmdl(&cmd_line); 
		if (str != NULL && cmd_line != NULL)
		{
			res = ft_exec(&cmd_line);
			if (res != 0)
			{
				if (res == 40)
					write(1, "pipe fails\n", 11);
				if (res == 50)
					write(1, "malloc error\n", 13);
				free(str);
				ft_clean_env();
				free_all(&cmd_line);
				return (1);
			}
		}
		}
	}
	
	//	print_cmdl(&cmd_line);
		if (str)
			free(str);
//		printf("free all entre\n");
		free_all(&cmd_line);
//		printf("free all sorti\n");
	//		cmd_line = cmd_line->next;

	}
	}
}
