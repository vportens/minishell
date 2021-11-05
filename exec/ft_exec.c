/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:44 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/05 04:22:11 by victor           ###   ########.fr       */
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

int     ft_execute_cmd(t_commande_line *cur)
{
    char **str;

    str = ft_t_env_to_enp(get_adress_env());
    if (str == NULL)
        return (50);
    cur->pid = fork();
    if (cur->pid == 0)
    {
		printf("argv[0] envoyer dans l'exec : %s\n", cur->argv[0]);
        execve(cur->argv[0], cur->argv, str);
		printf("commande echoue\n");
		// free_all; pb ici on est pas au cmd_line first solution on le rajout en parametre
		exit(1);
    }
	else
	{
		waitpid(cur->pid, NULL, 0);
		printf("wait pid\n");	
	}
    return (1);
}

int     ft_exec(t_commande_line	**s_cmd_line, char *str)
{
    t_commande_line *cur;
	int				i;
	int				nbr_fork;

	i = 0;
    cur = *s_cmd_line;
    if (cur->argv == NULL)
        return (0);
	while (cur)
	{
        if (cur->argv[0] == NULL)
            return (0);
		if (i == 0)
			nbr_fork = fill_fd(&cur);
		if  (i == 0 && cur->pipe[0] != -1 && ft_is_builtin(cur->argv[0]) && cur->next == NULL)
     	   ft_no_fork_exec(s_cmd_line, str);
		else if (cur->pipe[0] != -1)
        {
           	//if (ft_exist(cur))//securiser le retour 50
				cur->argv[0] = get_bin_argv_zero(cur->argv[0], ft_get_env("PATH")); // go avoir le path
			// 	if (cur->argv[0] == NULL)
			// 		return (50):
				printf("argv de cur en envoyer a exec : %s\n", cur->argv[0]);
                ft_execute_cmd(cur);
            //else
              //  ft_print_error("minishell :", cur->argv[0]);
        }
		cur = cur->next;
		i++;
	}
	// wait all pib active (if pipe[0] != -1 allor pid est active)
    return (0);
}
