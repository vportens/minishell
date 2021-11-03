/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:18:40 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/02 18:18:55 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_check_n(char **str)
{
    int i;
    int y;
    int cpt;

    cpt = 0;
    y = 0;
    i = 0;
    while (str[i] && ft_strlen(str[i]) >= 2)
    {
        if (str[i][y] == '-' && str[i][y + 1] == 'n')
        {
            y++;
            while (str[i][y] == 'n')
                y++;
            if (y == (int)ft_strlen(str[i]))
                cpt++;
        }
        else
            return (cpt);
        i++;
        y = 0;
    }
    return (cpt);
}

void    ft_built_in_echo(char **str)
{
    int i;
    int y;

    y = 0;
    i = ft_check_n(str);
    if (i > 0)
        y++;
    while (str[i])
    {
        printf("%s", str[i]);
        if (str[i + 1])
            printf(" ");
        i++;
    }
    if (y == 0)
        printf("\n");
}
