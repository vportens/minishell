/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:21:20 by laclide           #+#    #+#             */
/*   Updated: 2021/11/20 16:01:01 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int exit_status;

int	ft_sup_int(char *str)
{
	long	res;
	int		sig;
	int		i;

	res = 0;
	sig = 1;
	i = 0;
	if (str[i] == '-')
	{
		i++;
		sig = -1;
	}
	while (str[i])
	{
		res = res * 10 + str[i] - '0';
		i++;
		if (res > 2147483648)
			return (1);
	}
	res = res * sig;
	if (res > 2147483647)
		return (1);
	return (0);
}

int	ft_non_int(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			write(2, "minishell: exit: ", ft_strlen("minishell: exit: "));
			write(2, str, ft_strlen(str));
			write(2, ": numeric argument required\n", ft_strlen(": numeric argument required\n"));
			return (1);
		}
		i++;		
	}
	return (ft_sup_int(str));
}

int	exit_bltin(char **args, t_commande_line **first, pid_t *pid)
{
	int	ret;

	ret = 0;
	printf("exit\n");
	if (args[1] != NULL)
	{
		if (ft_non_int(args[1]))
		{
			ft_clean_env();
			free_all(first);
			free(pid);
			exit (1);
		}
		ret = ft_atoi(args[1]);
		if (args[2] != NULL)
		{
			write(2, "minishell: exit: too many arguments\n", ft_strlen("minishell: exit: too many arguments\n"));
			exit_status = 1;
			return (2);
		}
		free(pid);
		ft_clean_env();
		free_all(first);
		exit(ret);
	}
	free(pid);
	ft_clean_env();
	free_all(first);
	exit (0);
	return (0);
}

int	ft_exec_builtin(char *str, char **args, t_commande_line **first, pid_t *pid)
{
	int (*tb_tk[7])(char **) = {&ft_built_in_cd, &ft_built_in_echo, &ft_built_in_env, &ft_built_in_pwd, &ft_built_in_export, &ft_built_in_unset};
	char *built[7] = {"cd", "echo", "env", "pwd", "export", "unset", "exit"};
	int i;

	i = 0;
	free(pid);
	if (str == NULL)
			return (0);
	if (ft_strcmp("exit", str))
	{
		exit_bltin(args, first, pid);
		exit (1); // just not if not forking
		return (1);
	}
	while (i < 7 && !ft_strcmp(built[i], str))
		i++;
	if (i < 7)
		tb_tk[i](args);
	ft_clean_env();
	free_all(first); // free env;
	if (i < 7)
		return (0);
	return (0);
}

int	ft_exec_builtin_fd(char *str, char **args, t_commande_line **first, pid_t *pid)
{
	int (*tb_tk[7])(char **, int) = {&ft_built_in_cd, &ft_built_in_echo_fd, &ft_built_in_env_fd, &ft_built_in_pwd_fd, &ft_built_in_export_fd, &ft_built_in_unset};
	char *built[7] = {"cd", "echo", "env", "pwd", "export", "unset", "exit"};
	int i;

	i = 0;
	printf("enter exec builtin fd\n");
	if (str == NULL)
			return (0);
	if (ft_strcmp("exit", str))
	{
		exit_bltin(args, first, pid);
		return (1);
	}
	while (i < 7 && !ft_strcmp(built[i], str))
		i++;
	if (i < 7)
		tb_tk[i](args, (*first)->fd_out);
	if (i < 7)
		return (0);
	return (0);
}