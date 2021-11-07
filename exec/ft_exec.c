/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 19:24:44 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/07 18:47:47 by laclide          ###   ########.fr       */
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

/*
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
		printf("%d nbr_fork ,waitpid[%d] \n", nbr_fork, i);
		waitpid(pid[i], NULL, 0);
		i++;
	}
	printf("fin de l'excve\n");
	// wait all pib active (if pipe[0] != -1 allor pid est active)
    return (0);
}*/

void	close_fd_all(t_commande_line **cmdl)
{
	t_commande_line *cur;

	cur = *cmdl;
	while (cur)
	{
		if (cur->fd_in != 0)
			close(cur->fd_in);
		if (cur->fd_out != 1)
			close(cur->fd_out);
		cur = cur->next;	
	}
}

int	init_pipe(int **nfd, int i, t_commande_line *cur)
{
	nfd[i] = malloc(sizeof(int) * (2));
	if (nfd[i] == NULL)
		return (50);
	if (pipe(nfd[i]) == -1)
		return (40);
	if (i == 0)
		cur->fd_in = 0;
	else 
		cur->fd_in = nfd[i - 1][0];
	if (cur->next == NULL)
		cur->fd_out = 1;
	else
		cur->fd_out = nfd[i][1];
	return (0);
}

int	open_pipe(t_commande_line **cmdl)
{
	t_commande_line *cur;
	int				**nfd;
	int				i;
	int				ret;

	i = 0;
	cur = *cmdl;
	nfd = malloc(sizeof(int *) * (len_cmd(cur) + 1));
	if (nfd == NULL)
		return (50);
	nfd[len_cmd(cur)] = NULL;
	while (cur)
	{
		ret = init_pipe(nfd, i, cur);
		if (ret != 0)
			return (ret);
		cur = cur->next;
		i++;
	}
	return (0);
}

int	open_fd(t_commande_line **cmdl)
{
	t_token *cur;

	cur = (*cmdl)->first_token;
	while (cur)
	{
		if (cur->type == FILE_IN)
		{
			(*cmdl)->fd_in = open(cur->str, O_RDONLY);
			if ((*cmdl)->fd_in == -1)
			{
				write(1, "minishell: ", 11);
				perror(cur->str);
				return (-1);
			}
		}
		if (cur->type == FILE_OUT)
		{
			(*cmdl)->fd_out = open(cur->str, O_CREAT | O_RDWR | O_TRUNC, 0644);
			if ((*cmdl)->fd_out == -1)
				return (-1);
		}
		if (cur->type == FILE_OUT_OVER)
		{
			(*cmdl)->fd_out = open(cur->str, O_CREAT | O_RDWR | O_APPEND, 0644);
			if ((*cmdl)->fd_out == -1)
				return (-1);
		}
		cur = cur->next;
	}
	return (0);
}

char	**env_to_tabtab(t_env **envp)
{
	char	**new;
	t_env	*cur;
	int		i;

	i = 0;
	cur = *envp;
	while (cur)
	{
		cur = cur->next;
		i++;
	}
	new = malloc(sizeof(char *) * (i + 1));
	new[i] = NULL;
	cur = *envp;
	i = 0;
	while (cur)
	{
		new[i] = cur->str;
		i++;
		cur = cur->next;
	}
	return (new);

}

int	ft_execve_fct(t_commande_line **cmdl, t_commande_line **first)
{
	char	**str;

    str = env_to_tabtab(get_adress_env());
    if (str == NULL)
        return (50);
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
			exit(1);
		if (pid[i] == 0)
		{
		if (open_fd(&cur) != -1)
			ft_execve_fct(&cur, cmdl);
		}
//		printf("sortie de pipe\n");
		close_fd_all(cmdl);
//		if (cur->fd_in != 0)
//			close(cur->fd_in);
//		if (cur->fd_out != 1)
//			close(cur->fd_out);
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

//	printf("rentre dans ft_exec\n");
	cur = *cmdl;
	open_pipe(cmdl);
	pid = malloc(sizeof(pid_t) * len_cmd(cur));
	if (pid == NULL)
		return (50);
	res = forking(cmdl, pid);
//	printf("sort dans ft_exec\n");
	wait_pid(cmdl, pid);
	return (0);
}
