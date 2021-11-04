/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delete_key.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:21:22 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/04 10:34:22 by lchristo         ###   ########.fr       */
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
		if (len == ft_get_lenkey(cpy->str) && !ft_truestrncmp(cpy->str, key, len))
		{
			if (prev == NULL)
				*env = cpy->next;
			else
				prev->next = cpy->next;
			ft_free_env_elem(cpy);
			return ;
		}
		prev = cpy;
		cpy = cpy->next;
	}
}