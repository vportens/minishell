/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:21:22 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/02 12:01:56 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_delete_env(char *str)
{
	return (ft_singletone(str, DELETE));	
}

void	ft_delete_env_call(t_env **env, char *key)
{
	t_env *cpy;
	t_env *prev;
	int len;

	len = ft_get_lenkey(key);
	prev = NULL;
	cpy = *env;
	while (cpy)
	{
		if (!ft_truestrncmp(cpy->str, key, len))
		{
			if (prev == NULL)
				env = &cpy;
			else
				prev->next = cpy->next;
			ft_free_env_elem(cpy);
			return ;
		}
		prev = cpy;
		cpy = cpy->next;
	}
}