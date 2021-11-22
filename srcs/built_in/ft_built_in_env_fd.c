/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_env_fd.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:25:49 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 19:46:32 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_built_in_env_fd(char **str, int fd)
{
	t_env	**env;

	if (*str == NULL)
		return (0);
	env = get_adress_env();
	ft_built_in_show_env_fd(env, fd);
	return (0);
}

void	ft_built_in_show_env_fd(t_env **env, int fd)
{
	t_env	*cur;

	cur = *env;
	while (cur)
	{
		if (ft_is_equal(cur->str))
		{
			ft_putstr_fd(cur->str, fd);
			ft_putchar_fd('\n', fd);
		}
		cur = cur->next;
	}
}
