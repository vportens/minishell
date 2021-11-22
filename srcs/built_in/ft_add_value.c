/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_value.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 21:18:11 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 20:48:16 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_add_env(char *str)
{
	return (ft_singletone(str, ADD));
}

char	*ft_final_add(char *env)
{
	int		len;
	char	*s;
	int		i;
	int		y;

	i = 0;
	y = 0;
	len = ft_get_lenkey(env) - 1;
	if (env[ft_get_lenkey(env) - 1] != '+')
		return (ft_strdup(env));
	s = malloc(sizeof(char) * ft_strlen(env));
	if (s == NULL)
		return (NULL);
	while (env[y])
	{
		s[i] = env[y];
		i++;
		y++;
		if (y == len)
			y++;
	}
	s[i] = '\0';
	return (s);
}

int	ft_special_lenkey(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '=' && str[i] != '+')
		i++;
	return (i);
}

int	ft_add_value_to_env(t_env **env_list, char *env, int declare)
{
	int		len;
	t_env	*cpy;

	cpy = *env_list;
	len = ft_special_lenkey(env);
	while (cpy)
	{
		declare = cpy->declare;
		if (len == ft_get_lenkey(cpy->str) && !ft_strncmp(env, cpy->str, len))
		{
			if (ft_equal(cpy->str) && !ft_equal(env))
				return (0);
			free(cpy->str);
			cpy->str = ft_final_add(env);
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
