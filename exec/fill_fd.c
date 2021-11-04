/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_fd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laclide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:05:45 by laclide           #+#    #+#             */
/*   Updated: 2021/11/04 13:32:08 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_file_to_read_or_creat(enum type)
{
	if (type == FILE_IN || type == FILE_OUT || type == FILE_OUT_OVER || type == LIMITOR)
		return (1);
	return (0);
}

static int	fill_pipe(t_commande_line **stc, t_token *tok)
{
	int	ret;

	if (tok->type == FILE_IN)
	{
		ret = open(tok->str, O_RDONLY);
		(*stc)->pipe[0] = ret;
		return (ret);
	}
	if (tok->type == FILE_OUT)
	{
		ret = open(tok->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
		(*stc)->pipe[1] = ret;
		return (ret);
	}
	if (tok->type == FILE_OUT_OVER)
	{
		ret = open(tok->str, O_CREAT | O_RDWR | O_APPEND, 0644);
		(*stc)->pipe[1] = ret;
		return (ret);
	}
}

int	fill_fd(t_commande_line **stc)
{
	int				i;
	t_commande_line	*cur;
	t_token			*cur_t;
	int				file_out_last_cmd;

	i = 0;
	cur = *stc;
	while (cur)
	{
		if (i != 0)
			cur->pipe[0] = file_out_last_cmd;
		cur_t = cur->first_token;
		while (cur_t)
		{
			if (is_file_to_read_or_creat(cur_t->type))
			{
				if (fill_pipe(&cur, cur_t) == -1)
					return (-1); // return errono error
			}
			cur_t = cur_t->next;
		}
		file_out_last_cmd = pipe[1];
		i++;
		cur = cur->next;
	}
	return (0);
}
