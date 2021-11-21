/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_unset.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:11:00 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 19:41:15 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	exit_status;

int	ft_built_in_unset(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_singletone(str[i], DELETE) == 50)
			return (50);
		i++;
	}
	exit_status = 0;
	return (0);
}
