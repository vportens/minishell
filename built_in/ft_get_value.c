/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:19:46 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 20:10:04 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_str(char *str)
{
	t_env	**env_list;

	env_list = get_adress_env();
	return (ft_get_str_of_env(env_list, str));
}

char	*ft_get_str_of_env(t_env **env, char *str)
{
	t_env	*cpy;
	int		len;

	len = ft_get_lenkey(str);
	cpy = *env;
	while (cpy)
	{
		if (len == ft_get_lenkey(cpy->str) && !ft_strncmp(cpy->str, str, len))
			return (cpy->str);
		cpy = cpy->next;
	}
	return (NULL);
}

char	*ft_get_env(char *str)
{
	t_env	**env_list;

	env_list = get_adress_env();
	return (ft_get_value_of_env(env_list, str));
}

char	*ft_get_value_of_env(t_env **env, char *str)
{
	t_env	*cpy;
	int		len;

	len = ft_get_lenkey(str);
	cpy = *env;
	while (cpy)
	{
		if (len == ft_get_lenkey(cpy->str) && !ft_strncmp(cpy->str, str, len))
			return (cpy->str + len + 1);
		cpy = cpy->next;
	}
	return (NULL);
}
