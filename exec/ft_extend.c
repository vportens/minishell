/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_extend.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:41:26 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/04 15:29:14 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_is_path()
{
    char *path;
    char **multipath;
    int i;

    i = 0;
    path = ft_get_env("PATH");
    if (path == NULL)
        return (0);
    multipath = ft_strsplit(path, ':');
    if (multipath == NULL)
        return (50);
    while (multipath[i])
    {
        if (access(multipath[i], X_OK) == 0)
            return (1);
        i++;
    }
    ft_print_error("minishell :");
    return (0);
}

int ft_is_extendable()
{
    if (ft_is_path() == 1)
        return (1);
    return (0);
}