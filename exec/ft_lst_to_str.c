/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_to_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 17:30:59 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/08 14:59:35 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_t_envlen(void)
{
	t_env	*env;
	int		i;

	i = 1;
	env = *get_adress_env();
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

char	**ft_t_env_to_enp(t_env **envp)
{
	char	**str;
	t_env	*env;
	int		i;
	int		index;

	index = 0;
	i = ft_t_envlen();
	env = *envp;
	str = malloc(sizeof(char *) * i);
	if (str == NULL)
		return (NULL);
	while (env && index < i)
	{
		str[index] = ft_strdup(env->str);
		if (str[index] == NULL)
			return (NULL);
		index++;
		env = env->next;
	}
	return (str);
}
