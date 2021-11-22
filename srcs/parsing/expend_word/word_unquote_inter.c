/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_unquote_inter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:14:42 by laclide           #+#    #+#             */
/*   Updated: 2021/11/16 14:15:24 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*string_env(char *str, char *tmp, int *cur)
{
	char	*tmp2;

	tmp2 = NULL;
	tmp2 = get_env(cur, str);
	if (tmp2 == NULL)
		return (free_str_ret_null(tmp));
	return (tmp2);
}

char	*string_before_env(char *str, char *s1, int *cur, int start)
{
	char	*s2;
	char	*s3;

	s2 = NULL;
	s3 = NULL;
	s2 = malloc(sizeof(char) * ((*cur) - start + 1));
	if (s2 == NULL)
		return (free_str_ret_null(s1));
	s2 = ft_strncpy(s2, str + start, (*cur) - start);
	s3 = ft_strjoin(s1, s2);
	free_both(s1, s2);
	return (s3);
}

char	*end_word_unquote(char *str, char *s1, int *i, int j)
{
	char	*s2;
	char	*s3;

	s2 = NULL;
	s3 = NULL;
	if ((*i) - j == 0)
		return (s1);
	s2 = malloc(sizeof(char) * ((*i) - j + 1));
	if (s2 == NULL)
		return (free_str_ret_null(s1));
	s2 = ft_strncpy(s2, str + j, (*i) - j);
	s3 = ft_strjoin(s1, s2);
	free_both(s1, s2);
	return (s3);
}

char	*free_split_token(char **split, t_token *tok)
{
	free_split(split);
	if (tok)
	{
		if (tok->str)
			free(tok->str);
	}
	return (NULL);
}
