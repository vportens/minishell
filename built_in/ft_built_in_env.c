/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:25:49 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/02 14:21:42 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void ft_built_in_env(void)
{
    t_env **env;

    env = get_adress_env();
    ft_built_in_show_env(env);
}

int     ft_is_equal(char *str)
{
    int i;

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
	t_env			*cur;
	
	cur = *env;
	while(cur)
	{
        if (ft_is_equal(cur->str))
        	printf("%s\n",cur->str);
		cur = cur->next;
	}
}
