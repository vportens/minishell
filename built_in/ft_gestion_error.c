/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_gestion_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:02:06 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/03 19:09:04 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_print_error(char *str1, char *str2)
{
    char *ret;

    ret = ft_strjoin(str1, str2);
    if (ret == NULL)
        return (50);
    perror(ret);
    free(ret);
    return (0);
}