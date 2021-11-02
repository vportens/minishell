/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_till_double.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laclide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/24 19:30:25 by laclide           #+#    #+#             */
/*   Updated: 2021/11/02 20:14:24 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*env_doublequote(char *str, char *s1, int *i, int j)
{
	char	*s2;
	char	*s3;
	char	*s4;

	s2 = NULL;
	s3 = NULL;
	s4 = NULL;
	s2 = malloc(sizeof(char) * ((*i) - j + 1));
	if (s2 == NULL)
		return (free_str_ret_null(s1));
	s2 = ft_strncpy(s2, str + j, (*i) - j);
	s3 = ft_strjoin(s1, s2);
	free_both(s1, s2);
	if (s3 == NULL)
		return (NULL);
	s2 = NULL;
	s2 = get_env(i, str);
	if (s2 == NULL)
		return (free_str_ret_null(s3));
	s4 = ft_strjoin(s3, s2);
	free_both(s2, s3);
	return (s4);
}

char	*word_will_double(char *str, int *i, char *s1)
{
	int		j;
	char	*s2;
	char	*s3;

	j = *i;
	s2 = NULL;
	s3 = NULL;
	while (str && str[(*i)] && str[(*i)] != '"')
	{
		if (str[(*i)] == '$')
		{
			s1 = env_doublequote(str, s1, i, j);
			if (s1 == NULL)
				return (NULL);
			j = *i + 1;
		}
		(*i)++;
	}
	s2 = malloc(sizeof(char) * ((*i) - j + 1));
	if (s2 == NULL)
		return (free_str_ret_null(s1));
	s2 = ft_strncpy(s2, str + j, (*i) - j);
	s3 = ft_strjoin(s1, s2);
	free_both(s1, s2);
	return (s3);
}
