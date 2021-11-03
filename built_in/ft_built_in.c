/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laclide <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 17:21:20 by laclide           #+#    #+#             */
/*   Updated: 2021/11/03 14:59:48 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *str)
{
	if (str == NULL)
			return (0);
		if (ft_strcmp(str, "echo") || ft_strcmp(str, "cd") || ft_strcmp(str, "pwd") || ft_strcmp(str, "export") || ft_strcmp(str, "env") || ft_strcmp(str, "unset") || ft_strcmp(str, "exit"))
		return (1);
	return (0);
}
