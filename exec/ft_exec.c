/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:44 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/19 17:23:59 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/types.h>
#include <sys/stat.h>

int	exit_bltin(char **args);

int	ft_non_int(char *str);

int	ft_sup_int(char *str);

extern int	exit_status;

void	free_fd_all_exit_malloc_error(t_commande_line **first)
{
	close_fd_all(first);
	exit (50);
}

void	free_str_fd_exit_malloc_error(char **str, t_commande_line **first)
{
	free(str);
	close_fd_all(first);
	exit (50);
}

void	free_str_exit_fd_error(char **str)
{
	free(str);
	exit(1);
}

int	ft_exec_cmd(t_commande_line **cmdl, char **str)
{
	struct stat	buff;

	printf("passe dans ft exec cmd\n");
	execve((*cmdl)->argv[0], (*cmdl)->argv, str);
	printf("lol\n");
	if (stat((*cmdl)->argv[0], &buff) == 0)
	{
		write(2, "minishell: ", ft_strlen("minishell: "));
		write(2, (*cmdl)->argv[0], ft_strlen((*cmdl)->argv[0]));
		write(2, ": Permission denied\n", ft_strlen(": Permission denied\n"));
		exit(126);
	}
	write(2, "minishell: ", ft_strlen("minishell: "));
	write(2, (*cmdl)->argv[0], ft_strlen((*cmdl)->argv[0]));
	write(2, ": No such file or directory\n", ft_strlen(": No such file or directory\n"));
	exit_status = 127;
	exit(exit_status);
	return (0);
}

int	exec_builtin(char **str, t_commande_line **cmdl)
{
	free(str);
	if (ft_exec_builtin((*cmdl)->argv[0], (*cmdl)->argv) == 2)
		exit(1);
	exit(0);
	return (0);
}

int	ft_execve_fct(t_commande_line **cmdl, t_commande_line **first)
{
	char		**str;

	str = env_to_tabtab(get_adress_env());
	if (str == NULL)
		free_fd_all_exit_malloc_error(first);
	if (ft_is_builtin((*cmdl)->argv[0]) == 0)
		(*cmdl)->argv[0] = get_bin_argv_zero((*cmdl)->argv[0],
				ft_get_env("PATH"));
	if ((*cmdl)->argv[0] == NULL)
		free_str_fd_exit_malloc_error(str, first);
	dup2((*cmdl)->fd_in, STDIN_FILENO);
	dup2((*cmdl)->fd_out, STDOUT_FILENO);
	if ((*cmdl)->name_file != NULL)
	{
		unlink((*cmdl)->name_file);
		free((*cmdl)->name_file);
	}
	close_fd_all(first);
	if ((*cmdl)->fd_in < 0 || (*cmdl)->fd_out < 0)
		free_str_exit_fd_error(str);
	if (ft_is_builtin((*cmdl)->argv[0]))
		exec_builtin(str, cmdl);
	else
		ft_exec_cmd(cmdl, str);
	return (0);
}

int	no_forking(t_commande_line **cmdl)
{
	if ((*cmdl)->argv == NULL)
		return (0);
	if (ft_strcmp((*cmdl)->argv[0], "exit"))
	{
		exit_bltin((*cmdl)->argv);
		return (1);
	}
	else if (ft_exec_builtin((*cmdl)->argv[0], (*cmdl)->argv) != 0)
	{
		return (0);
	}
	return (0);
}

int	multi_fork(pid_t *pid, int i, t_commande_line **cmdl, t_commande_line **cur)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	pid[i] = fork();
	if (pid[i] == -1)
		exit(1);
	if (pid[i] == 0)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ft_execve_fct(cur, cmdl);
	}
	if ((*cur)->fd_in != 0)
		close((*cur)->fd_in);
	if ((*cur)->fd_out != 1)
		close((*cur)->fd_out);
	return (0);
}

int	forking(t_commande_line **cmdl, pid_t *pid)
{
	int				len;
	int				i;
	t_commande_line	*cur;

	i = 0;
	cur = *cmdl;
	len = len_cmd(cur);
	while (cur)
	{
		open_fd(&cur);
		cur = cur->next;
	}
	cur = *cmdl;
	if (len == 1 && ft_is_builtin(cur->argv[0]))
		return (no_forking(cmdl));
	while (i < len)
	{
		multi_fork(pid, i, cmdl, &cur);
		cur = cur->next;
		i++;
	}
	return (0);
}

int	wait_pid(t_commande_line **cmdl, pid_t *pid)
{
	t_commande_line	*cur;
	int				len;
	int				i;

	i = 0;
	cur = *cmdl;
	len = len_cmd(cur);
	if (len == 1 && ft_is_builtin((*cmdl)->argv[0]))
		return (0);
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

int	ft_exec(t_commande_line **cmdl)
{
	t_commande_line	*cur;
	pid_t			*pid;
	int				ret;

	cur = *cmdl;
	ret = open_pipe(cmdl);
	if (ret != 0)
		return (ret);
	pid = malloc(sizeof(pid_t) * len_cmd(cur));
	if (pid == NULL)
		return (50);
	forking(cmdl, pid);
	signal(SIGINT, signal_cmd);
	signal(SIGQUIT, SIG_IGN);
	wait_pid(cmdl, pid);
	free(pid);
	return (0);
}
