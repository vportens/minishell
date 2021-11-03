/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:58:15 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/02 16:53:15 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    ft_built_in_show_export(void)
{
    t_env **env;

    env = get_adress_env();
    ft_show_export(env);
}

int		ft_built_in_export(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_singletone(str[i], ADD) == 50)
			return (50);
		i++;
	}
	return (0);
}

void	ft_show_export(t_env **env)
{
	t_env			*cur;
	int				len;
	
	cur = *env;
	while(cur)
	{
		len = ft_get_lenkey(cur->str);
		printf("export %.*s", len, cur->str);
		if (len < (int)ft_strlen(cur->str))
			printf("=\"%s\"", cur->str + len + 1);
		printf("\n");
		cur = cur->next;
	}
}
