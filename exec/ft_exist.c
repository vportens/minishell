/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exist.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 12:41:26 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/05 04:24:01 by victor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_expend(t_commande_line *cmd_line)
{
    char *path;
    char *tmp;
    char *tmp2;
    char **multipath;
    int i;

    i = 0;
    path = ft_get_env("PATH");
    if (path == NULL)
        return (0);
    multipath = ft_strsplit(path, ':');
    if (multipath == NULL)
        return (50);
    while (multipath[i])
    {
        tmp = ft_strjoin(multipath[i], "/");
        tmp2 = ft_strjoin(tmp, cmd_line->argv[0]);
        free(multipath[i]);
        free(tmp);
        if (access(tmp2, X_OK) == 0)
            return (1);
        free(tmp2);
        i++;
    }
    return (0);
}

int ft_test_exist(t_commande_line *cmd_line)
{
    if (access(cmd_line->argv[0], X_OK) == 0)
        return (1);
    return (0);
}

int ft_exist(t_commande_line *cmd_line)
{
    if (!(cmd_line->argv[0][0] == '.' || cmd_line->argv[0][0] == '/'))
    {
        if (ft_expend(cmd_line))
            return (1);
    }
    else if (ft_test_exist(cmd_line) == 1)
        return (1);
    return (0);
}


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
		return (NULL);
	while (split_path[i])
	{
		ret = try_acces(str, split_path[i]);
		if (ret == 1)
		{
			try = get_acces(str, split_path[i]);
			free(str);
			return (try);
		}
		if (ret == 50)
		{
			free(str);
			return (NULL);
		}
		i++;
	}
	return (str);
}
