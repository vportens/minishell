/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 21:58:48 by laclide           #+#    #+#             */
/*   Updated: 2021/11/21 22:08:04 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_cmdl(t_commande_line *new)
{
	new->string = NULL;
	new->first_token = NULL;
	new->argv = NULL;
	new->name_file = NULL;
	new->next = NULL;
}

static void	go_to_the_pipe(int *i, char *str)
{
	t_quote	quote;

	quote = NONE;
	while (str[*i])
	{
		quote = update_quote_status(str[*i], quote);
		if (str[*i] == '|' && quote == NONE)
			return ;
		(*i)++;
	}
	return ;
}

static int	create_and_fill_cmd(char *str, int cur, int start,
		t_commande_line **first)
{
	t_commande_line	*new;

	new = malloc(sizeof(t_commande_line));
	if (new == NULL)
		return (50);
	init_cmdl(new);
	new->string = malloc(sizeof(char) * (cur - start + 1));
	if (new->string == NULL)
		return (free_cmdl_ret_malloc_error(new));
	new->string = ft_strncpy(new->string, str + start, cur - start);
	cmdl_add_back(first, new);
	return (0);
}

int	get_cmd_line(char *string, t_commande_line **first_stc)
{
	int	cur;
	int	start;

	cur = 0;
	start = 0;
	while (string[cur])
	{
		if (cur != 0)
		{
			cur++;
			start++;
		}
		go_to_the_pipe(&cur, string);
		if (create_and_fill_cmd(string, cur, start, first_stc) > 0)
			return (50);
		start = cur;
		if (cur == 0)
		{
			cur++;
			start++;
		}
	}
	return (0);
}
