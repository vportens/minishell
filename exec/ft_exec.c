/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:44 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/05 11:33:41 by laclide          ###   ########.fr       */
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

int     ft_execute_cmd(t_commande_line *cur, pid_t **pid, int *i)
{
    char **str;

    str = ft_t_env_to_enp(get_adress_env());
    if (str == NULL)
        return (50);
    (*pid)[*i] = fork();
    if ((*pid)[*i] == 0)
    {
		printf("argv[0] envoyer dans l'exec : %s\n", cur->argv[0]);
        execve(cur->argv[0], cur->argv, str);
		printf("commande echoue\n");
		// free_all; pb ici on est pas au cmd_line first solution on le rajout en parametre
		exit(1);
    }
	return (0);
}

int     ft_exec(t_commande_line	**s_cmd_line, char *str)
{
    t_commande_line *cur;
	int				i;
	int				j;
	int				nbr_fork;
	pid_t			*pid;

	i = 0;
	j = 0;
    cur = *s_cmd_line;
    if (cur->argv == NULL)
        return (0);
	while (cur)
	{
        if (cur->argv[0] == NULL)
            return (0);
		if (i == 0)
		{
			nbr_fork = fill_fd(&cur);
			pid = malloc(sizeof(pid_t) * nbr_fork);
			if (pid == NULL)
				return (50);
		}
		if  (i == 0 && cur->pipe[0] != -1 && ft_is_builtin(cur->argv[0]) && cur->next == NULL)
     	   ft_no_fork_exec(s_cmd_line, str);
		else if (cur->pipe[0] != -1)
        {
				cur->argv[0] = get_bin_argv_zero(cur->argv[0], ft_get_env("PATH")); // go avoir le path
			 	if (cur->argv[0] == NULL)
			 		return (50);
				printf("argv de cur en envoyer a exec : %s\n", cur->argv[0]);
                ft_execute_cmd(cur, &pid, &j);
				j++;
        }
		cur = cur->next;
		i++;
	}
	i = 0;
	while (i < nbr_fork)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	printf("fin de l'excve\n");
	// wait all pib active (if pipe[0] != -1 allor pid est active)
    return (0);
}
