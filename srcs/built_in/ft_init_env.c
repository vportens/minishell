/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:22:01 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 19:31:43 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_init_env(t_env **env_list)
{
	char	*s;

	s = ft_strjoin("PWD=", getcwd(NULL, 0));
	if (s == NULL)
		return (50);
	if (ft_push_front("SHLVL=1", env_list, 1) == 50)
	{
		ft_clean_envlist(env_list);
		return (50);
	}
	if (ft_push_front(s, env_list, 1) == 50)
	{
		free(s);
		ft_clean_envlist(env_list);
		return (50);
	}
	free(s);
	if (ft_push_front("OLDPWD", env_list, 1) == 50)
	{
		ft_clean_envlist(env_list);
		return (50);
	}
	return (0);
}

t_env	**get_adress_env(void)
{
	static t_env	*new = NULL;

	return (&new);
}

int	ft_init_t_env(char **env)
{
	t_env	**env_list;
	int		i;

	env_list = get_adress_env();
	i = 0;
	while (env[i])
		i++;
	if (i == 0)
		if (ft_init_env(env_list) == 50)
			return (50);
	i--;
	while (i >= 0)
	{
		if (ft_push_front(env[i], env_list, 0) == 50)
		{
			ft_clean_envlist(env_list);
			return (50);
		}
		i--;
	}
	return (0);
}
