/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_end_stc.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 23:24:45 by viporten          #+#    #+#             */
/*   Updated: 2021/11/21 23:27:50 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_token(t_commande_line **cmd_line)
{

	t_token			*tok;

	while ((*cmd_line)->first_token)
	{ 
		tok = (*cmd_line)->first_token->next;
		if ((*cmd_line)->first_token->str)
			free((*cmd_line)->first_token->str);
		free((*cmd_line)->first_token);
		(*cmd_line)->first_token = tok;
	}
}