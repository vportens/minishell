/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 18:13:55 by viporten          #+#    #+#             */
/*   Updated: 2021/11/21 18:19:01 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	exit_status;

int	wait_pid(t_commande_line **cmdl, pid_t *pid)
{
	t_commande_line	*cur;
	int				len;
	int				i;

	i = 0;
	cur = *cmdl;
	len = len_cmd(cur);
	if (len == 1 && ft_is_builtin((*cmdl)->argv[0]))
	{
		return (0);
	}
	while (i < len)
	{
		waitpid(pid[i], &exit_status, 0);
		if (WIFEXITED(exit_status))
			exit_status = WEXITSTATUS(exit_status);
		else if (WIFSIGNALED(exit_status))
			exit_status = 128 + WTERMSIG(exit_status);
		i++;
	}
	return (0);
}

int	no_forking(t_commande_line **cmdl, pid_t *pid)
{
	printf("stdin : %d\nstdout : %d\n", (*cmdl)->fd_in, (*cmdl)->fd_out);
	if ((*cmdl)->argv == NULL)
		return (0);
	else if (ft_exec_builtin_fd((*cmdl)->argv[0],
			(*cmdl)->argv, cmdl, pid) != 0)
	{
		return (0);
	}
	return (0);
}

int	exec_builtin(char **str, t_commande_line **cmdl,
	t_commande_line **first, pid_t *pid)
{
	free(str);
	if (ft_exec_builtin((*cmdl)->argv[0], (*cmdl)->argv, first, pid) == 2)
		exit(1);
	exit(0);
	return (0);
}

void	signal_cmd_2(int sig)
{
	exit_status += sig;
	if (sig == 2)
	{
		exit_status = 130;
		printf("\n");
		rl_replace_line("", 0);
		rl_redisplay();
	}
}
