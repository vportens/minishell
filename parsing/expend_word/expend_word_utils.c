/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_word_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:49:27 by laclide           #+#    #+#             */
/*   Updated: 2021/11/21 22:13:20 by viporten         ###   ########.fr       */
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

int	is_type_file(t_e_token type)
{
	if (type == CREAT_FILE || type == WRITE_FILE
		|| type == OPEN_FILE || type == HERE_DOC)
		return (1);
	return (0);
}

int	ret_file_without_obj(t_e_token type)
{
	write(2, "minishell: erreur de syntaxe",
		ft_strlen("minishell: erreur de syntaxe"));
	if (type == NON)
		write(2, " newline\n", 9);
	if (type == CREAT_FILE)
		write(2, " >\n", 3);
	else if (type == WRITE_FILE)
		write(2, " >>\n", 4);
	else if (type == OPEN_FILE)
		write(2, " <\n", 3);
	else if (type == HERE_DOC)
		write(2, " <<\n", 4);
	return (12);
}

t_e_token	cp_type_change_file(t_e_token type, int *file)
{
	*file = 1;
	return (type);
}
