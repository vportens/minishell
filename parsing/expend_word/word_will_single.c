/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_will_single.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 17:37:57 by laclide           #+#    #+#             */
/*   Updated: 2021/11/04 11:08:16 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*word_will_single(char *str, int *i, char *s1)
{
	char	*s2;
	char	*s3;
	int		j;

	s2 = NULL;
	s3 = NULL;
	j = *i;
	while (str && str[(*i)] && str[(*i)] != '\'')
		(*i)++;
	s2 = malloc(sizeof(char) * ((*i) - j + 1));
	if (s2 == NULL)
	{
		if (s1)
			free(s1);
		return (NULL);
	}
	s2 = ft_strncpy(s2, str + j, (*i) - j);
	s3 = ft_strjoin(s1, s2);
	if (s1)
		printf("string in till)single : %s\n", s1);
	if (s2)
		printf("string s2 in till)single : %s\n", s2);
	free_both(s1, s2);
//	printf("passage de free)both dans word till single\n");
	return (s3);
}
