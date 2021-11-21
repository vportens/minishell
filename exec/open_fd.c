/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 19:14:44 by laclide           #+#    #+#             */
/*   Updated: 2021/11/21 22:11:22 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_file_in(t_commande_line **cmdl, t_token *cur, t_e_token type)
{
	if (type == FILE_IN)
	{
		if ((*cmdl)->fd_in != 0)
			close((*cmdl)->fd_in);
		(*cmdl)->fd_in = open(cur->str, O_RDONLY);
		if ((*cmdl)->fd_in == -1)
		{
			write(1, "minishell: ", 11);
			perror(cur->str);
			return (-1);
		}
	}
	else if (type == LIMITOR)
	{
		if ((*cmdl)->fd_in != 0)
			close((*cmdl)->fd_in);
		(*cmdl)->fd_in = create_heredoc_fd(cmdl, &cur);
		if ((*cmdl)->fd_in == -1)
			return (-1);
	}
	return (0);
}

int	redirect_file_out(t_commande_line **cmdl, t_token *cur, t_e_token type)
{
	if (type == FILE_OUT)
	{
		if ((*cmdl)->fd_out != 1)
			close((*cmdl)->fd_out);
		(*cmdl)->fd_out = open(cur->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		if ((*cmdl)->fd_out == -1)
			return (-1);
	}
	else if (type == FILE_OUT_OVER)
	{
		if ((*cmdl)->fd_out != 1)
			close((*cmdl)->fd_out);
		(*cmdl)->fd_out = open(cur->str, O_CREAT | O_RDWR | O_APPEND, 0644);
		if ((*cmdl)->fd_out == -1)
			return (-1);
	}
	return (0);
}

int	open_fd(t_commande_line **cmdl)
{
	t_token	*cur;

	cur = (*cmdl)->first_token;
	while (cur)
	{
		if (cur->type == FILE_IN || cur->type == LIMITOR)
			if (redirect_file_in(cmdl, cur, cur->type) == -1)
				return (-1);
		if (cur->type == FILE_OUT || cur->type == FILE_OUT_OVER)
			if (redirect_file_out(cmdl, cur, cur->type) == -1)
				return (-1);
		cur = cur->next;
	}
	return (0);
}
