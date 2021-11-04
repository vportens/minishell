/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:41:26 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/04 17:11:33 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_expend(t_commande_line *cmd_line)
{
    char *path;
    char *tmp;
    char *tmp2;
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
        tmp = ft_strjoin(multipath[i], "/");
        tmp2 = ft_strjoin(tmp, cmd_line->argv[0]);
        free(multipath[i]);
        free(tmp);
        if (access(tmp2, X_OK) == 0)
            return (1);
        free(tmp2);
        i++;
    }
    return (0);
}

int ft_test_exist(t_commande_line *cmd_line)
{
    if (access(cmd_line->argv[0], X_OK) == 0)
        return (1);
    return (0);
}

int ft_exist(t_commande_line *cmd_line)
{
    if (!(cmd_line->argv[0][0] == '.' || cmd_line->argv[0][0] == '/'))
    {
        if (ft_expend(cmd_line))
            return (1);
    }
    else if (ft_test_exist(cmd_line) == 1)
        return (1);
    return (0);
}