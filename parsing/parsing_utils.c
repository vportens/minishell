/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laclide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:04:51 by laclide           #+#    #+#             */
/*   Updated: 2021/11/02 23:23:49 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_separator(char c)
{
	if (c == ' ' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	is_redirection(char c)
{
	if (c == '<' || c == '>')
		return (1);
	return (0);
}

e_quote	update_quote_status(char c, e_quote quote)
{
	if (c == '"')
	{
		if (quote == NONE)
			return (DOUBLE);
		else if (quote == DOUBLE)
			return (NONE);
	}
	else if (c == '\'')
	{
		if (quote == NONE)
			return (SINGLE);
		else if (quote == SINGLE)
			return (NONE);
	}
	return (quote);
}

e_quote	update_quote_succes(t_token *stc, int *i, e_quote quote)
{
	(*i)++;
	stc->expanded = true;
	return (quote);
}

int	unclose_quote(char	*str)
{
	int		i;
	e_quote	quote;

	i = 0;
	quote = NONE;
	while (str[i])
	{
		if (str[i] == '"')
		{
			if (quote == NONE)
				quote = DOUBLE;
			else if (quote == DOUBLE)
				quote = NONE;
		}
		if (str[i] == '\'')
		{
			if (quote == NONE)
				quote = SINGLE;
			else if (quote == SINGLE)
				quote = NONE;
		}
		i++;
	}
	return (quote);
}
