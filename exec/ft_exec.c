/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:44 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/04 13:50:50 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int     ft_exec(t_commande_line	**cmd_line, char *str)
{
    int             ret;
    t_commande_line *cpy;

    if (str == NULL || *cmd_line == NULL)
        return (0);
    cpy = *cmd_line;
    if (cpy->argv == NULL)
        return (0);
	fill_fd(cmd_line);
    if (ft_exec_builtin(cpy->argv[0],cpy->argv) == 2)
    {
        if (cpy->argv[1] != NULL)
            ret = ft_atoi(cpy->argv[1]);
        else
            ret = 0;
        free_all(cmd_line);
        free(str);
        exit(ret);
    }
    printf("end ft_exec\n");
        return 1 ;
//    printf("%s\n", str);
//    printf("%s\n", cpy->argv[0]);
    return (0);
}
