/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 18:54:15 by laclide           #+#    #+#             */
/*   Updated: 2021/11/20 18:17:21 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_nfd(int **nfd)
{
	int	i;

	i = 0;
	while (nfd[i])
	{
		free(nfd[i]);
		i++;
	}
	free(nfd);
}

void	close_fd_all(t_commande_line **cmdl)
{
	t_commande_line	*cur;

	cur = *cmdl;
	while (cur)
	{
		if (cur->fd_in != 0)
			close(cur->fd_in);
		if (cur->fd_out != 1)
			close(cur->fd_out);
		cur = cur->next;
	}
}

int	init_pipe(int **nfd, int i, t_commande_line *cur)
{
	nfd[i] = malloc(sizeof(int) * (2));
	if (nfd[i] == NULL)
		return (50);
	if (pipe(nfd[i]) == -1)
		return (40);
	if (i == 0)
		cur->fd_in = 0;
	else
		cur->fd_in = nfd[i - 1][0];
	if (cur->next == NULL)
	{
		close(nfd[i][0]);
		close(nfd[i][1]);
		cur->fd_out = 1;
	}
	else
		cur->fd_out = nfd[i][1];
	return (0);
}

int	open_pipe(t_commande_line **cmdl)
{
	t_commande_line	*cur;
	int				**nfd;
	int				i;
	int				ret;

	i = 0;
	cur = *cmdl;
	nfd = malloc(sizeof(int *) * (len_cmd(cur) + 1));
	if (nfd == NULL)
		return (50);
	nfd[len_cmd(cur)] = NULL;
	while (cur)
	{
		ret = init_pipe(nfd, i, cur);
		if (ret != 0)
		{
			free_nfd(nfd);
			return (ret);
		}
		cur = cur->next;
		i++;
	}
	free_nfd(nfd);
	return (0);
}
