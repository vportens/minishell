/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 00:26:24 by laclide           #+#    #+#             */
/*   Updated: 2021/11/03 14:05:33 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	word_modif_two(t_token **stc, char *duplica, e_quote quote, e_quote prec)
{
	char	*s1;
	int		cur;
	char	*str;

	str = ft_strdup(duplica);
	if (duplica)
		free(duplica);
	cur = 0;
	s1 = NULL;
	while (str[cur])
	{
		quote = update_quote_status(str[cur], quote);
		if (prec != quote)
			prec = update_quote_succes(*stc, &cur, quote);
		else
		{
			if (quote == SINGLE)
				s1 = word_will_single(str, &cur, s1);
			else if (quote == DOUBLE)
				s1 = word_will_double(str, &cur, s1);
			else if (quote == NONE)
				s1 = word_will_unquote(stc, str, &cur, s1);
			if (s1 == NULL)
			{
				free(str);
				return (50);
			}
		}
	}
	free(str);
	(*stc)->str = s1;
	return (0);
}

int	word_modif(t_token **stc, char *str, e_token token)
{
	char	*s1;
	int		i;
	e_quote	quote;
	e_quote	prec;

	i = 0;
	quote = NONE;
	prec = NONE;
	s1 = NULL;
	if (token == LIMITOR)
		return (limitor(*stc, str));
	return (word_modif_two(stc, str, quote, prec));
}

int	is_type_file(e_token type)
{
	if (type == CREAT_FILE || type == WRITE_FILE || type == OPEN_FILE
		|| type == HERE_DOC)
		return (1);
	return (0);
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
					return (12);
				cur_t->type = LIMITOR;
				limiter = 0;
			}
			cur_t = cur_t->next;
		}
		if (limiter == 1)
			return (12);
		cur_b = cur_b->next;
	}
	return (0);
}

e_token	change_type_file(e_token type, int *file)
{
	*file = 0;
	if (type == OPEN_FILE)
		return (FILE_IN);
	else if (type == CREAT_FILE)
		return (FILE_OUT);
	else if (type == WRITE_FILE)
		return (FILE_OUT_OVER);
	return (NON);
}

e_token	cp_type_change_file(e_token type, int *file)
{
	*file = 1;
	return (type);
}

int	check_open_fil(t_commande_line **block)
{
	t_commande_line	*cur_b;
	t_token			*cur_t;
	int				file;
	e_token			type;

	cur_b = *block;
	file = 0;
	while (cur_b)
	{
		cur_t = cur_b->first_token;
		while (cur_t)
		{
			if (is_type_file(cur_t->type) == 1 && file == 1)
				return (12);
			else if (is_type_file(cur_t->type) == 1)
				type = cp_type_change_file(cur_t->type, &file);
			else if (file == 1 && cur_t->str && (cur_t->str[0] != '\0'))
				cur_t->type = change_type_file(type, &file);
			cur_t = cur_t->next;
		}
		if (file == 1)
			return (12);
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
				printf("enter in word_modif avec str to modif :%s\\n\n", cur_t->str);
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
