/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:25:49 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 19:33:17 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_built_in_env(char **str)
{
	t_env	**env;

	if (*str == NULL)
		return (0);
	env = get_adress_env();
	ft_built_in_show_env(env);
	return (0);
}

int	ft_is_equal(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

void	ft_built_in_show_env(t_env **env)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_is_equal(cur->str))
		{
			printf("%s\n", cur->str);
		}
		cur = cur->next;
	}
}
