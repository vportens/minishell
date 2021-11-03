/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_builtin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 22:11:14 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/03 23:45:14 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin(char *str)
{
	char *built[7] = {"cd", "echo", "env", "pwd", "export", "unset", "exit"};
	int i;

	i = 0;
	if (str == NULL)
			return (0);
//	printf("start ftstrcmp\n");
	while (i < 7 && !ft_strcmp(built[i], str))
	{
//		printf("i : %d\n", i);
		i++;
	}
//	printf("end ftstrcmp\n");

	if(i < 7)
		return 1;
	return (0);
}
