/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laclide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 08:58:02 by laclide           #+#    #+#             */
/*   Updated: 2021/11/03 18:00:49 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	free_all(t_commande_line **cmd_line)
{
	t_commande_line *tmp;
	t_token			*tok;

	if (cmd_line)
	{
	while (*cmd_line)
	{
		printf("start_free_all\n");
		tmp = (*cmd_line)->next;
		if ((*cmd_line)->string)
			free((*cmd_line)->string);

		printf("free_all_string\n");
		if ((*cmd_line)->argv)
			free((*cmd_line)->argv);
		printf("free_all_argv\n");
		if ((*cmd_line)->first_token)
		{
			while ((*cmd_line)->first_token)
			{
				printf("start_free_all_token\n");
				tok = (*cmd_line)->first_token->next;
				if ((*cmd_line)->first_token->str)
					free((*cmd_line)->first_token->str);
				free((*cmd_line)->first_token);
				(*cmd_line)->first_token = tok;

				printf("end_free_all_token\n");
			}
		}
		free((*cmd_line));
		printf("end_free_all_cmd\n");
		
		*cmd_line = tmp;
	}
	}
}

int	main(int ac, char **av, char **envp)
{
	char			*str;
	int				i;
	int				res;
	t_commande_line	*cmd_line;
	
//	get_environment(envp);
	g_envp = envp;
	cmd_line = NULL;
	i = 0;
	while (1)
	{
		str = readline("minishell$> ");
		i++;
		if (str == NULL)
		{
			free_all(&cmd_line);
			write(1, "readline return NULL\n", ft_strlen("readline return NULL\n"));
			return (1);
		}
		res = unclose_quote(str);
		if (res > 0)
		{
			write(1, "unclose quote\n", 14);
			free_all(&cmd_line);
		}
		else
		{
			write(1, "entre dans get_cmd_line\n", ft_strlen("entre dans get_cmd_line\n"));
			if (get_cmd_line(str, &cmd_line) > 0)		/* ici on malloc et remplit cmd_line->string*/
			{
				free_all(&cmd_line);
				free(str);
				write(1, "malloc error\n", ft_strlen("malloc error\n"));
				return (50); // clean all arg;
			}
			write(1, "get_cmd_line		succes\n", ft_strlen("get_cmd_line		succes\n"));
			write(1, "entre dans split_arg\n", ft_strlen("entre dans split_arg\n"));
			if (split_all_cmdl_string_to_token(&cmd_line) > 0) /* ici on malloc les token et on remplit token->str et init token->type*/
			{
				free_all(&cmd_line);
				free(str);
				write(1, "malloc error\n", ft_strlen("malloc error\n"));
				return (50); // clean all arg
			}
			write(1, "split_arg			success\n", ft_strlen("split_arg			success\n"));
			write(1, "entre dans expend_word\n", ft_strlen("entre dans expend_word\n"));
			
			res = expend_words(&cmd_line);
			if (res != 0)
			{
				free_all(&cmd_line);
				if (res == 50)
				{
					free(str);
					write(1, "malloc error\n", ft_strlen("malloc error\n"));
					return (50);
				}
			//	if (res == 12)
		//			write(1, "*************************************\n*         erreur de syntaxe         *\n*************************************\n", ft_strlen("*************************************\n*         erreur de syntaxe         *\n*************************************\n"));
				
			}
			
			if (organise_arg(&cmd_line) != 0)
			{
					write(1, "malloc error\n", ft_strlen("malloc error\n"));
					free_all(&cmd_line);
					free(str);
					return (50);
			}
			write(1, "expend_word		success\n", ft_strlen("expend_word		success\n"));

			
		//	write(1, "pars_cmd_line\n", ft_strlen("pars_cmd_line\n"));
		}
		i = 0;
		t_commande_line	*tmp;
		t_token	*first;

		tmp = cmd_line;
		while (cmd_line)
		{
			printf("cmd_line n %d to exec: %s\\n\n", i, cmd_line->string);
			first = cmd_line->first_token;
			while (cmd_line->first_token)
			{
				printf("	word : %s\\n\n", cmd_line->first_token->str);
				printf("	type : ");
				if (cmd_line->first_token->type == 0)
					printf("NONE\n");
				if (cmd_line->first_token->type == 1)
					printf("ARG\n");
				if (cmd_line->first_token->type == 2)
					printf("BUILTIN\n");
				if (cmd_line->first_token->type == 3)
					printf("OPEN_FILE\n");
				if (cmd_line->first_token->type == 4)
					printf("HERE_DOC\n");
				if (cmd_line->first_token->type == 5)
					printf("LIMITOR\n");
				if (cmd_line->first_token->type == 6)
					printf("CREAT_FILE\n");
				if (cmd_line->first_token->type == 7)
					printf("WRITE_FILE\n");
				if (cmd_line->first_token->type == 8)
					printf("FILE_IN\n");
				if (cmd_line->first_token->type == 9)
					printf("FILE_OUT\n");
				if (cmd_line->first_token->type == 10)
					printf("FILE_OUT_OVER\n");
				if (cmd_line->first_token->expanded == 0)
					printf("	expanded : FALSE\n");
				if (cmd_line->first_token->expanded == 1)
					printf("	expanded : TRUE\n");
				cmd_line->first_token = cmd_line->first_token->next;  
			}
			i = 0;
			cmd_line->first_token = first;
			while (cmd_line->argv[i])
			{
				printf("	argv[%d] : %s\n", i, cmd_line->argv[i]);
				i++;
			}
			cmd_line = cmd_line->next;
			printf("end of lst word\n");
		}
		cmd_line = tmp;
		if (str)
			free(str);
		printf("last free all\n");
		free_all(&cmd_line);
	//		cmd_line = cmd_line->next;

	}
}
