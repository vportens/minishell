/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:21:11 by laclide           #+#    #+#             */
/*   Updated: 2021/11/16 14:14:30 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_token(t_token *new)
{
	new->str = NULL;
	new->type = NON;
	new->expanded = false;
	new->next = NULL;
}

void	init_type(t_token *new)
{
	int	len;

	len = 0;
	if (new->str)
		len = ft_strlen(new->str);
	if (len == 1)
	{
		if (new->str[0] == '<')
			new->type = OPEN_FILE;
		else if (new->str[0] == '>')
			new->type = CREAT_FILE;
	}
	if (len == 2)
	{
		if (new->str[0] == '<' && new->str[1] == '<')
			new->type = HERE_DOC;
		if (new->str[0] == '>' && new->str[1] == '>')
			new->type = WRITE_FILE;
	}
	if (ft_is_builtin(new->str))
		new->type = BUILTIN;
	if (new->type == NON && len != 0)
		new->type = ARG;
}
