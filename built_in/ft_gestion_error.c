/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:02:06 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 19:25:49 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	exit_status;

int	ft_print_error(char *str1, char *str2)
{
	char	*ret;

	exit_status = 1;
	ret = ft_strjoin(str1, str2);
	if (ret == NULL)
		return (50);
	perror(ret);
	free(ret);
	return (0);
}
