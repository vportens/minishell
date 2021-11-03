/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push_front.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:30:18 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/01 21:33:00 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_push_front(char *env, t_env **begin_lst)
{
	t_env *env_new;
	
	env_new = malloc(sizeof(t_env));
	if (env_new == NULL)
		return (50);
	env_new->str = ft_strdup(env);
	if (env_new->str == NULL)
		return (50);
	env_new->next = *begin_lst;
	*begin_lst = env_new;
	return (0);
}