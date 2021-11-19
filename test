/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:41:26 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/19 14:08:07 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int exit_status;

char	*get_acces(char *str, char *path)
{
	char	*back_slash;
	char	*new;

	back_slash = ft_strjoin(path, "/");
	if (back_slash == NULL)
		return (NULL);
	new = ft_strjoin(back_slash, str);
	free(back_slash);
	if (new == NULL)
		return (NULL);
	return (new);
}

int	try_acces(char *str, char *path)
{
	char	*try;

	try = get_acces(str, path);
	if (try == NULL)
		return (50);
	if (access(try, X_OK) == 0)
	{
		free(try);
		return (1);
	}
	free(try);
	return (0);
}

char	*get_bin_argv_zero(char *str, char *path)
{
	int		i;
	int		ret;
	char	**split_path;
	char	*try;

	i = 0;
	if (str && (str[0] == '.' || str[0] == '/'))
		return (str);
	split_path = ft_strsplit(path, ':');
	if (split_path == NULL)
	{
		write(2, "minishell: ", 11);
		write(2, str, ft_strlen(str));
		write(2, " : commande introuvable\n", ft_strlen(" : commande introuvable\n"));
		free(str);
		return (NULL);
	}
	while (split_path[i] && str[0] != '\0')
	{
		ret = try_acces(str, split_path[i]);
		if (ret == 1)
		{
			try = get_acces(str, split_path[i]);
			free_split(split_path);
			return (try);
		}
		if (ret == 50)
		{
			free_split(split_path);
			return (NULL);
		}
		i++;
	}
	free_split(split_path);
	write(2, "minishell: ", 11);
	write(2, str, ft_strlen(str));
	write(2, " : commande introuvable\n", ft_strlen(" : commande introuvable\n"));
	exit_status = 127;
	return (str);
}
