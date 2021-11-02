/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_word.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 00:26:24 by laclide           #+#    #+#             */
/*   Updated: 2021/11/02 20:47:49 by laclide          ###   ########.fr       */
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
				printf("modif word fail\n");
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
		return (limitor(*stc, str));//leaks
	return (word_modif_two(stc, str, quote, prec));
}

int	edit_type(t_commande_line **block)
{
	t_commande_line	*cur_b;
	t_token			*cur_t;
	int				limiter;

	cur_b = *block;
	limiter = 0;
	while (cur_b)
	{
		cur_t = cur_b->first_token;
		while (cur_t)
		{
			if (cur_t->type == HERE_DOC)
				limiter = 1;
			else if (limiter == 1 && cur_t->str && cur_t->str[0] != '\0')
			{
				if (cur_t->type == CREAT_FILE || cur_t->type == WRITE_FILE || cur_t->type == OPEN_FILE || cur_t->type == HERE_DOC)
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
			if ((cur_t->type == OPEN_FILE || cur_t->type == CREAT_FILE || cur_t->type == WRITE_FILE || cur_t->type == HERE_DOC) && file == 1)
				return (12);
			else if (cur_t->type == OPEN_FILE || cur_t->type == CREAT_FILE || cur_t->type == WRITE_FILE)
			{
				type = cur_t->type;
				file = 1;
			}
			else if (file == 1 && cur_t->str && (cur_t->str[0] != '\0'))
			{
				if (type == OPEN_FILE)
					cur_t->type = FILE_IN;
				else if (type == CREAT_FILE)
					cur_t->type = FILE_OUT;
				else if (type == WRITE_FILE)
					cur_t->type = FILE_OUT_OVER;
				printf("test str : %s\\n\n", cur_t->str);
				file = 0;
			}
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
	if (edit_type(block) != 0 || check_open_fil(block) != 0)
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
				res = word_modif(&cur_t, cur_t->str, cur_t->type);//leaks
				if (res != 0)
					return (50);
			}
			cur_t = cur_t->next;
		}
		cur_b = cur_b->next;
	}
	return (0);
}
