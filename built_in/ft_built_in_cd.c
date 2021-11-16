/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:52:54 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/16 12:42:17 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_built_in_cd(char **str)
{
    if (*(str + 1) == NULL)
	{
		*(str + 1) = ft_get_value_of_env(get_adress_env(), "HOME");
		if (*(str + 1) == NULL || str[1][0] == '\0')
			return (0);
	}
	if (chdir(*(str + 1)) == -1)
        if (ft_print_error("minishell: cd: ", *(str + 1)) == 50)
            return (50);
    return (0);
}