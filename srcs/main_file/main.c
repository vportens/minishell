/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 08:58:02 by laclide           #+#    #+#             */
/*   Updated: 2021/11/22 17:12:35 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	g_exit_status;

int	pars(char *str, t_commande_line **cmd_line)
{
	int	res;

	res = unclose_quote(str);
	if (res > 0)
	{
		write(2, "minishell: miss quote\n", 22);
		free_all(cmd_line);
	}
	else
	{
		if (get_cmd_line(str, cmd_line) > 0)
			return (free_str_all_ret_malloc_error(cmd_line, str));
		if (split_all_cmdl_string_to_token(cmd_line) > 0)
			return (free_str_all_ret_malloc_error(cmd_line, str));
		res = expend_words(cmd_line);
		if (res != 0)
		{
			free_all(cmd_line);
			if (res == 50)
				return (free_str_ret_malloc_error(str));
		}
		if (organise_arg(cmd_line) != 0)
			return (free_str_all_ret_malloc_error(cmd_line, str));
	}
	return (res);
}

void	signal_cmd(int sig)
{
	g_exit_status += sig;
	if (sig == 2)
	{
		g_exit_status = 130;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	if (sig == SIGQUIT)
	{
		write(2, "Quit (core dumped)\n", ft_strlen("Quit (core dumped)\n"));
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

void	go_to_exec(t_commande_line **cmd_line, char *str)
{
	int	res;

	res = pars(str, cmd_line);
	if (res == 50)
	{
		free_all_env_str_ret_malloc_error(cmd_line, str);
		exit (1);
	}
	if (res == 0)
	{
		if (str != NULL && *cmd_line != NULL)
		{
			res = ft_exec(cmd_line);
			if (res != 0)
			{
				free_all_error(cmd_line, str, res);
				exit (1);
			}
		}
	}
}

int	main(int ac, char **av, char **envp)
{
	char			*str;
	t_commande_line	*cmd_line;

	cmd_line = NULL;
	g_exit_status = 0;
	ft_init_t_env(envp);
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, SIG_IGN);
	if (!ac && !av)
		return (0);
	while (1)
	{
		str = readline("minishell$> ");
		add_history(str);
		signal(SIGINT, signal_cmd);
		signal(SIGQUIT, SIG_IGN);
		if (str == NULL)
			return (print_exit_free_env_all(&cmd_line));
		if (check_str(str) != 0)
			error_str();
		else
			go_to_exec(&cmd_line, str);
		free_end(&cmd_line, str);
	}
}
