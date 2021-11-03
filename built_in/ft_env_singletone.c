/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_singletone.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 08:59:11 by victor            #+#    #+#             */
/*   Updated: 2021/11/02 14:16:11 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_get_lenkey(char *env)
{
	int i;

	i = 0;
	while (env[i] != '\0' && env[i] != '=')
		i++;
	return (i);
}

int		ft_singletone(char *str, int mode)
{
	t_env	**env_list;

	env_list = get_adress_env();
	if (mode == DELETE)
	{
		ft_delete_env_call(env_list, str);
		return (0);	
	}
	if (mode == FREE)
		ft_clean_envlist(env_list);
	if (mode == ADD)
		if (ft_add_value_to_env(env_list, str) == 50)
		{
			ft_clean_envlist(env_list);
			return (50);
		}
	return (0);
}
