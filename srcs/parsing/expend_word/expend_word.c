/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 00:26:24 by laclide           #+#    #+#             */
/*   Updated: 2021/11/21 22:22:39 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_modif_two(t_token **stc, char *duplica, t_quote quote, t_quote prec)
{
	char	*s1;
	int		cur;
	char	*str;

	if (init_str(&str, duplica, &cur, &s1) == NULL)
		return (50);
	while (str[cur])
	{
		quote = update_quote_status(str[cur], quote);
		if (prec != quote)
			prec = update_quote_succes(*stc, &cur, quote, &s1);
		else
		{
			if (quote == SINGLE)
				s1 = word_will_single(str, &cur, s1);
			else if (quote == DOUBLE)
				s1 = word_will_double(str, &cur, s1);
			else if (quote == NONE)
				s1 = word_will_unquote(stc, str, &cur, s1);
		}
		if (s1 == NULL)
			return (free_str_ret_malloc_error(str));
	}
	return (end_modif_two(str, stc, s1));
}

int	word_modif(t_token **stc, char *str, t_e_token token)
{
	t_quote	quote;
	t_quote	prec;

	quote = NONE;
	prec = NONE;
	if (token == LIMITOR)
		return (limitor(*stc, str));
	return (word_modif_two(stc, str, quote, prec));
}

int	edit_type(t_commande_line **block, int limiter)
{
	t_commande_line	*cur_b;
	t_token			*cur_t;

	cur_b = *block;
	while (cur_b)
	{
		cur_t = cur_b->first_token;
		while (cur_t)
		{
			if (cur_t->type == HERE_DOC)
				limiter = 1;
			else if (limiter == 1 && cur_t->str && cur_t->str[0] != '\0')
			{
				if (is_type_file(cur_t->type) == 1)
					return (ret_file_without_obj(cur_t->type));
				cur_t->type = LIMITOR;
				limiter = 0;
			}
			cur_t = cur_t->next;
		}
		if (limiter == 1)
			return (ret_file_without_obj(NON));
		cur_b = cur_b->next;
	}
	return (0);
}

int	check_open_fil(t_commande_line **block)
{
	t_commande_line	*cur_b;
	t_token			*cur_t;
	int				file;
	t_e_token		type;

	cur_b = *block;
	file = 0;
	while (cur_b)
	{
		cur_t = cur_b->first_token;
		while (cur_t)
		{
			if (is_type_file(cur_t->type) == 1 && file == 1)
				return (ret_file_without_obj(cur_t->type));
			else if (is_type_file(cur_t->type) == 1)
				type = cp_type_change_file(cur_t->type, &file);
			else if (file == 1 && cur_t->str && (cur_t->str[0] != '\0'))
				cur_t->type = change_type_file(type, &file);
			cur_t = cur_t->next;
		}
		if (file == 1)
			return (ret_error_file_without_file(cur_b->next));
		cur_b = cur_b->next;
	}
	return (0);
}

int	expend_words(t_commande_line **block)
{
	t_commande_line	*cur_b;
	t_token			*cur_t;
	int				res;

	cur_b = *block;
	if (edit_type(block, 0) != 0 || check_open_fil(block) != 0)
		return (12);
	res = 0;
	while (cur_b)
	{
		cur_t = cur_b->first_token;
		while (cur_t)
		{
			if (cur_t->str && cur_t->str[0] != '\0')
			{
				res = word_modif(&cur_t, cur_t->str, cur_t->type);
				if (res != 0)
					return (50);
			}
			cur_t = cur_t->next;
		}
		cur_b = cur_b->next;
	}
	return (0);
}
