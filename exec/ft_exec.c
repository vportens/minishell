/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:44 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/04 16:04:12 by laclide          ###   ########.fr       */
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
    t_commande_line *cur;
	int				i;

	i = 0;
    cur = *s_cmd_line;
    if (cur->argv == NULL)
        return (0);
	while (cur)
	{
		if (i == 0 && fill_fd(&cur) && cur->pipe[0] == -1)
			printf("erno error\n");
		else if  (i == 0 && ft_is_builtin(cur->argv[0]) && cur->next == NULL)
     	   ft_no_fork_exec(s_cmd_line, str);
		else
           	if (ft_is_extendable())
		cur = cur->next;
		i++;
	}
    return (0);
}
