/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_echo.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 17:18:40 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/19 19:13:11 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int exit_status;

int    ft_built_in_echo_fd(char **str, int fd)
{
    int i;
    int y;

    str++;
    y = 0;
    i = ft_check_n(str);
    if (i > 0)
        y++;
    while (str[i])
    {
        ft_putstr_fd(str[i], fd);
        if (str[i + 1])
            ft_putchar_fd(' ', fd);
        i++;
    }
    if (y == 0)
        ft_putchar_fd('\n', fd);
    exit_status = 0; 
    return (0);
}
