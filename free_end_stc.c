/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end_stc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 23:24:45 by viporten          #+#    #+#             */
/*   Updated: 2021/11/21 23:47:20 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	free_token(t_commande_line **cmd_line)
{
	t_token	*tok;

	while ((*cmd_line)->first_token)
	{
		tok = (*cmd_line)->first_token->next;
		if ((*cmd_line)->first_token->str)
			free((*cmd_line)->first_token->str);
		free((*cmd_line)->first_token);
		(*cmd_line)->first_token = tok;
	}
}

int	free_all(t_commande_line **cmd_line)
{
	t_commande_line	*tmp;

	if (cmd_line)
	{
		while (*cmd_line)
		{
			tmp = (*cmd_line)->next;
			if ((*cmd_line)->string)
				free((*cmd_line)->string);
			if ((*cmd_line)->argv)
				free((*cmd_line)->argv);
			if ((*cmd_line)->first_token)
				free_token(cmd_line);
			if ((*cmd_line)->name_file)
				free((*cmd_line)->name_file);
			free((*cmd_line));
			*cmd_line = tmp;
		}
	}
	return (1);
}

void	error_str(void)
{
	write(2, "minishell: syntax error near unexpected token '|' \n",
		ft_strlen("minishell: syntax error near unexpected token '|' \n"));
	g_exit_status = 2;
}
