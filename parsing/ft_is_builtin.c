/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:11:14 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 20:53:05 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *str)
{
	if (str == NULL)
		return (0);
	if (ft_strcmp("exit", str))
		return (2);
	if (ft_strcmp("cd", str))
		return (1);
	else if (ft_strcmp("echo", str))
		return (1);
	else if (ft_strcmp("env", str))
		return (1);
	else if (ft_strcmp("pwd", str))
		return (1);
	else if (ft_strcmp("export", str))
		return (1);
	else if (ft_strcmp("unset", str))
		return (1);
	return (0);
}
