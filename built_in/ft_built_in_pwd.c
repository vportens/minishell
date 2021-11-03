/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_pwd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:57:54 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/03 23:29:13 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int    ft_built_in_pwd(char **str)
{
    char *pwd;

    if (*str == NULL)
        return (0);
    pwd = getcwd(NULL, 0);
    if (pwd == NULL)
        return (50);
    printf("%s\n", pwd);
    free(pwd);
    return (0);
}