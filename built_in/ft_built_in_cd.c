/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_cd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 21:52:54 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/16 13:17:08 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_equal(char *str)
{
	int		i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_get_home(void)
{
	t_env *cpy;
	int		len;

	len = ft_get_lenkey("HOME=");
	cpy = *get_adress_env();
	while (cpy)
	{
		if (len == ft_get_lenkey(cpy->str) && !ft_truestrncmp(cpy->str, "HOME", len))
		{
			if (ft_equal(cpy->str))
				return (cpy->str + len + 1);
			return (NULL);
		}
		cpy = cpy->next;
	}
	return (NULL);
}

int    ft_built_in_cd(char **str)
{
    if (*(str + 1) == NULL)
	{
		*(str + 1) = ft_get_home();
		if (*(str + 1) == NULL)
		{
			printf("HOME not set\n");
			return (0);
		}
		if (str[1][0] == '\0')
			return (0);
	}
	if (chdir(*(str + 1)) == -1)
        if (ft_print_error("minishell: cd: ", *(str + 1)) == 50)
            return (50);
    return (0);
}