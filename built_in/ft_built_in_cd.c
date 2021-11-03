/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:52:54 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/03 19:08:40 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_built_in_cd(char *str)
{
	if (chdir(str) == -1)
        if (ft_print_error("minishell: cd: ", str) == 50)
            return (50);
    return (0);
}