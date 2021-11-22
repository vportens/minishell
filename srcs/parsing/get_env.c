/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 20:08:09 by laclide           #+#    #+#             */
/*   Updated: 2021/11/21 22:21:19 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

int	get_len_env_var(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		str++;
	if (str[0] && str[0] == '?')
		return (1);
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

char	*alloc_dollar(int *cur)
{
	char	*new;

	*cur = *cur + 1;
	new = malloc(sizeof(char) * 2);
	if (new)
	{
		new[0] = '$';
		new[1] = '\0';
		return (new);
	}
	return (NULL);
}

char	*get_envp(char *str, int *cur)
{
	int		len_str;
	char	*cpy;
	char	*env;

	cpy = NULL;
	len_str = get_len_env_var(str);
	if (len_str == 0)
		return (alloc_dollar(cur));
	if (len_str == 1 && str[1] == '?')
	{
		*cur = *cur + 2;
		return (ft_itoa(g_exit_status));
	}
	cpy = malloc(sizeof(char) * (len_str + 1));
	if (cpy == NULL)
		return (NULL);
	cpy = ft_strncpy(cpy, str + 1, len_str);
	env = ft_get_env(cpy);
	free(cpy);
	if (env == NULL)
		return (fake_env(cur, len_str));
	*cur = *cur + len_str + 1;
	cpy = ft_strdup(env);
	return (cpy);
}

char	*get_env(int *cur, char *str)
{
	char	*s3;

	s3 = get_envp(str + *cur, cur);
	return (s3);
}
