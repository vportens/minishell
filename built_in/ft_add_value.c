/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:18:11 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/16 15:30:52 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_add_env(char *str)
{
	return (ft_singletone(str, ADD));	
}

int		ft_add_value_to_env(t_env **env_list, char *env)
{
	int len;
	int declare;
	t_env *cpy;

	declare = 0;
	cpy = *env_list;
	len = ft_get_lenkey(env);
	while (cpy)
	{
		declare = cpy->declare;
		if (len == ft_get_lenkey(cpy->str) && !ft_truestrncmp(env, cpy->str, len))
		{
			free(cpy->str);
			cpy->str = ft_strdup(env);
			if (cpy->str == NULL)
			{
				ft_clean_envlist(get_adress_env());
				return (50);
			}
			return (0);
		}
		cpy = cpy->next;
	}
	return (ft_push_front(env, env_list, declare));
}

