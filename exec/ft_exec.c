/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:44 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/04 15:16:38 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_no_fork_exec(t_commande_line **cmd_line, char *str)
{
    t_commande_line *cpy;
    int             ret;

    cpy = *cmd_line;
    if (ft_exec_builtin(cpy->argv[0], cpy->argv) == 2)
    {
        if (cpy->argv[1] != NULL)
            ret = ft_atoi(cpy->argv[1]);
        else
            ret = 0;
        free_all(cmd_line);
        free(str);
        exit(ret);
    }
}

int     ft_exec(t_commande_line	**s_cmd_line, char *str)
{
    t_commande_line *cmd_line;

    cmd_line = *s_cmd_line;
    if (cmd_line->argv == NULL)
        return (0);
    if  (ft_is_builtin(cmd_line->argv[0]) && cmd_line->next == NULL)
        ft_no_fork_exec(s_cmd_line, str);
    else
    {
        while (cmd_line)
        {
            if (ft_is_extendable())
            cmd_line = cmd_line->next;
        }
    }
    return (0);
}