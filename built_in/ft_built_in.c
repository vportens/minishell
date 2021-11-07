/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:21:20 by laclide           #+#    #+#             */
/*   Updated: 2021/11/07 18:19:27 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exec_builtin(char *str, char **args)
{
	int (*tb_tk[7])(char **) = {&ft_built_in_cd, &ft_built_in_echo, &ft_built_in_env, &ft_built_in_pwd, &ft_built_in_export, &ft_built_in_unset};
	char *built[7] = {"cd", "echo", "env", "pwd", "export", "unset", "exit"};
	int i;

	i = 0;
	if (str == NULL)
			return (0);
	if (ft_strcmp("exit", str))
		return (2);
	while (i < 7 && !ft_strcmp(built[i], str))
		i++;
	if (i < 7)
		tb_tk[i](args);
	if (i < 7)
		return (0);
	return (0);
}
