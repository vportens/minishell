/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 23:22:21 by laclide           #+#    #+#             */
/*   Updated: 2021/11/03 22:58:58 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_add_back_token(int cur, int start, char *str,
		t_commande_line **stc)
{
	t_token	*new;

	printf("rentre ds create add back\n");
	new = malloc(sizeof(t_token));
	if (new == NULL)
		return (50);
	printf("rentre dans init\n");
	init_token(new);
	printf("sort d'init\n");
	new->str = malloc(sizeof(char *) * (cur - start + 1));
	if (new->str == NULL)
		return (free_token_ret_malloc_error(new));
	new->str = ft_strncpy(new->str, str + start, cur - start);
	printf("start init new \n");

	init_type(new);
	printf("	go to token add back\n");
	token_add_back(&((*stc)->first_token), new);
	printf("end create add back\n");
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
	e_quote	quote;

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
	printf("bite\n");
	printf("len : %d\n", len);
	while (cur < len)
	{
		printf("	entre dans will\n");
		while (cur < len && (*stc)->string[cur] == ' ')
			cur++;
		start = cur;
		if ((*stc)->string[cur] && is_redirection((*stc)->string[cur]))
			iter_to_end_or_redirection((*stc)->string, &cur);
		else
		{
			printf("	go to iter\n");
			iter_to_end_arg(&cur, (*stc)->string);
			printf("	end to iter\n");			
		}
		if (create_add_back_token(cur, start, (*stc)->string, stc) > 0)
			return (50);
		printf("	end dans will\n");

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
		printf("start split\n");
		if (split_string_cur_cmdl(&cur) > 0)
			return (50);
		cur = cur->next;
	}
	return (0);
}
