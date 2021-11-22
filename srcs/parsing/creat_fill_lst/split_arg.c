/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 23:22:21 by laclide           #+#    #+#             */
/*   Updated: 2021/11/21 22:08:07 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_add_back_token(int cur, int start, char *str,
		t_commande_line **stc)
{
	t_token	*new;

	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (50);
	init_token(new);
	new->str = malloc(sizeof(char *) * (cur - start + 1));
	if (new->str == NULL)
		return (free_token_ret_malloc_error(new));
	new->str = ft_strncpy(new->str, str + start, cur - start);
	init_type(new);
	token_add_back(&((*stc)->first_token), new);
	return (0);
}

static void	iter_to_end_or_redirection(char	*str, int *cur)
{
	char	c;

	c = str[*cur];
	while (str[*cur] && str[*cur] == c)
		(*cur)++;
}

int	iter_to_end_arg(int *cur, char *str)
{
	t_quote	quote;

	quote = NONE;
	while (str[(*cur)])
	{
		quote = update_quote_status(str[*cur], quote);
		if (is_separator(str[*cur]) == 1 && quote == NONE)
			break ;
		(*cur)++;
	}
	return (0);
}

/*ici on decoupe la string en arg*/
/*tester create_add_back_token == NULL*/
static int	split_string_cur_cmdl(t_commande_line **stc)
{
	int		cur;
	int		start;
	int		len;

	cur = 0;
	len = 0;
	if ((*stc)->string != NULL)
		len = ft_strlen((*stc)->string);
	while (cur < len)
	{
		while (cur < len && (*stc)->string[cur] == ' ')
			cur++;
		start = cur;
		if ((*stc)->string[cur] && is_redirection((*stc)->string[cur]))
			iter_to_end_or_redirection((*stc)->string, &cur);
		else
		{
			iter_to_end_arg(&cur, (*stc)->string);
		}
		if (create_add_back_token(cur, start, (*stc)->string, stc) > 0)
			return (50);
	}
	return (0);
}

/* ici on passe sur chaque commande line et on va les envoyer faire split */
/*la commande line en different token et stocker le mot dans token->str*/
int	split_all_cmdl_string_to_token(t_commande_line **first)
{
	t_commande_line	*cur;

	cur = *first;
	while (cur)
	{
		if (split_string_cur_cmdl(&cur) > 0)
			return (50);
		cur = cur->next;
	}
	return (0);
}
