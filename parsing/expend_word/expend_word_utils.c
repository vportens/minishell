/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laclide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:49:27 by laclide           #+#    #+#             */
/*   Updated: 2021/11/09 19:39:01 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_str(char **str, char *duplica, int *cur, char **s1)
{
	*s1 = NULL;
	*cur = 0;
	*str = ft_strdup(duplica);
	free(duplica);
	if (*str == NULL)
		return (NULL);
	return (*str);
}

int	end_modif_two(char *str, t_token **stc, char *s1)
{
	free(str);
	(*stc)->str = s1;
	return (0);
}

int	is_type_file(e_token type)
{
	if (type == CREAT_FILE || type == WRITE_FILE || type == OPEN_FILE || type == HERE_DOC)
		return (1);
	return (0);
}

int	ret_file_without_obj(e_token type)
{
	write(1, "*************************************\n*         erreur de syntaxe", ft_strlen("*************************************\n*        erreur de syntaxe"));
	if (type == NON)
		write(1, " newline\n", 9);
	if (type == CREAT_FILE)
		write(1, " >\n", 3);
	else if (type == WRITE_FILE)
		write(1, " >>\n", 4);
	else if (type == OPEN_FILE)
		write(1, " <\n", 3);
	else if (type == HERE_DOC)
		write(1, " <<\n", 4);
	return (12);
}

e_token	cp_type_change_file(e_token type, int *file)
{
	*file = 1;
	return (type);
}
