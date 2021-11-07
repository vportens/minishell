/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:44 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/07 19:40:52 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_execve_fct(t_commande_line **cmdl, t_commande_line **first)
{
	char	**str;

    str = env_to_tabtab(get_adress_env());
    if (str == NULL)
	{
		printf("BItE\n");
        return (50);
	}
	if (ft_is_builtin((*cmdl)->argv[0]) == 0)
		(*cmdl)->argv[0] = get_bin_argv_zero((*cmdl)->argv[0], ft_get_env("PATH"));
	dup2((*cmdl)->fd_in, STDIN_FILENO);
	dup2((*cmdl)->fd_out, STDOUT_FILENO);
	close_fd_all(first);
	if ((*cmdl)->fd_in < 0 || (*cmdl)->fd_out < 0)
		exit(1);
	if (ft_is_builtin((*cmdl)->argv[0]))
	{
		if (ft_exec_builtin((*cmdl)->argv[0], (*cmdl)->argv) == 2)
		{
			exit(1);
		}
	}
	else
	{
//	printf("go execve\n");
//	printf("avec argv[0] : %s, str : %s\n", (*cmdl)->argv[0], str[0]);
	execve((*cmdl)->argv[0], (*cmdl)->argv, str);
//	printf("execve fail\n");

	exit(1);
	}
}

int	no_forking(t_commande_line **cmdl)
{
	int	ret;

	if (ft_exec_builtin((*cmdl)->argv[0], (*cmdl)->argv) == 2)
    {
        if ((*cmdl)->argv[1] != NULL)
            ret = ft_atoi((*cmdl)->argv[1]);
        else
            ret = 0;
      //  free_all(cmdl);
        exit(ret);
    }
	return (0);
}


int	forking(t_commande_line **cmdl, pid_t *pid)
{
	int	len;
	int	i;
	t_commande_line	*cur;

	i = 0;
	cur = *cmdl;
	len = len_cmd(cur);	
	if (len == 1 && ft_is_builtin(cur->argv[0]))
		return (no_forking(cmdl));
	while (i < len)
	{
		pid[i] = fork();
		if (pid[i] == -1)
			exit(1); // kill all ;
		if (pid[i] == 0)
		{
		if (open_fd(&cur) != -1)
			ft_execve_fct(&cur, cmdl);
		}
		close_fd_all(cmdl);
		cur = cur->next;
		i++;
	}
//	printf("end of forking\n");
	return (0);
}

int	wait_pid(t_commande_line **cmdl, pid_t *pid)
{
	t_commande_line *cur;
	int				len;
	int				i;

	i = 0;
	cur = *cmdl;
	len = len_cmd(cur);
	if (len == 1 && ft_is_builtin((*cmdl)->argv[0]))
		return (0);
	while (i < len)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	return (0);
}

int	ft_exec(t_commande_line **cmdl, char *str )
{
	t_commande_line	*cur;
	int				res;
	pid_t			*pid;
	int				ret;

//	printf("rentre dans ft_exec\n");
	cur = *cmdl;
	ret = open_pipe(cmdl);
	if (ret != 0)
		return (ret);
	pid = malloc(sizeof(pid_t) * len_cmd(cur));
	if (pid == NULL)
		return (50);
	res = forking(cmdl, pid);
//	printf("sort dans ft_exec\n");
	wait_pid(cmdl, pid);
	free(pid);
	return (0);
}
