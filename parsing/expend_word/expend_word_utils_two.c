/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expend_word_utils_two.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laclide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 18:56:16 by laclide           #+#    #+#             */
/*   Updated: 2021/11/03 19:04:53 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ret_error_file_without_file(t_commande_line *cur_b)
{
	write(1, "*************************************\n*         erreur de syntaxe", ft_strlen("*************************************\n*         erreur de syntaxe"));
	if (cur_b)
		write(1, " |\n", 3);
	else
		write(1, " newline\n", 9);
	return (12);
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
