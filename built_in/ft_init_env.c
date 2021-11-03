/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:22:01 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/02 16:07:17 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	**get_adress_env(void)
{
	static t_env *new = NULL;
    return (&new);
}

int		ft_init_t_env(char **env)
{
	t_env	**env_list;
	int	i;

	env_list = get_adress_env();
	i = 0;
	while (env[i])
		i++;
		
	i--;
	while (i >= 0)
	{
		if (ft_push_front(env[i], env_list) == 50)
			ft_clean_envlist(env_list);
		i--;
	}
	return (0);
}