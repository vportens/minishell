/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:57:54 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/19 14:03:09 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int exit_status;

int    ft_built_in_pwd(char **str)
{
    char *pwd;

    if (*str == NULL)
        return (0);
    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
        return (50);
    exit_status = 0;
    printf("%s\n", pwd);
    free(pwd);
    return (0);
}