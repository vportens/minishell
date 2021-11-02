/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlormois <mlormois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 20:08:09 by laclide           #+#    #+#             */
/*   Updated: 2021/11/02 23:06:59 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_len_env_var(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		str++;
	while (str[i] && (ft_is_alpha_num(str[i]) == 0 || str[i] == '_'))
		i++;
	return (i);
}

int	is_env(char *str, char *env, int len)
{
	int	i;

	i = 0;
	while (str[i] && i < len)
	{
		if (str[i] == '\0' || env[i] == '\0')
			return (-1);
		if (str[i] != env[i])
			return (-1);
		i++;
	}
	if (env[i] && env[i] == '=')
		return (0);
	return (-1);
}

char	*alloc_dollar(void)
{
	char	*new;

	new = malloc(sizeof(char) * 2);
	if (new)
	{
		new[0] = '$';
		new[1] = '\0';
		return (new);
	}
	return (NULL);
}

char	*get_envp(char *str, int *j)
{
	int		i;
	int		len_str;
	char	*cpy;

	i = 0;
	cpy = NULL;
	len_str = get_len_env_var(str);
	if (len_str == 0)
	{
		*j = *j + 1;
		return (alloc_dollar());
	}
	while (g_envp[i] && len_str != 0)
	{
		if (is_env(str + 1, g_envp[i], len_str) != -1)
		{
			cpy = ft_strdup(g_envp[i] + (len_str + 1));
			*j = *j + len_str + 1;
			return (cpy);
		}
		i++;
	}
	return (fake_env(j, len_str));
}

char	*get_env(int *cur, char *str)
{
	char	*s3;
	char	start_env;

	start_env = *cur;
	s3 = get_envp(str + *cur, cur);
	return (s3);
}
