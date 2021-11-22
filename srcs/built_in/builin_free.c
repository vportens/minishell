/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builin_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 20:38:16 by viporten          #+#    #+#             */
/*   Updated: 2021/11/21 20:42:44 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	free_in_builin(t_commande_line **first, pid_t *pid, int ret)
{
	free(pid);
	free_all(first);
	ft_clean_env();
	exit (ret);
	return (ret);
}
