/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_word_utils_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:56:16 by laclide           #+#    #+#             */
/*   Updated: 2021/11/21 22:13:08 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_error_file_without_file(t_commande_line *cur_b)
{
	write(2, "minishell: erreur de syntaxe",
		ft_strlen("minishell: erreur de syntaxe"));
	if (cur_b)
		write(2, " |\n", 3);
	else
		write(2, " newline\n", 9);
	return (12);
}

t_e_token	change_type_file(t_e_token type, int *file)
{
	*file = 0;
	if (type == OPEN_FILE)
		return (FILE_IN);
	else if (type == CREAT_FILE)
		return (FILE_OUT);
	else if (type == WRITE_FILE)
		return (FILE_OUT_OVER);
	else if (type == HERE_DOC)
		return (LIMITOR);
	return (NON);
}
