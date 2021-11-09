/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by rmechety          #+#    #+#             */
/*   Updated: 2021/11/09 22:29:17 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "struct.h"

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/ft_exist.c                           */
/* -------------------------------------------------------------------------- */
char	*get_acces(char *str, char *path);
int	try_acces(char *str, char *path);
char	*get_bin_argv_zero(char *str, char *path);

/* -------------------------------------------------------------------------- */
/*                        FILE = exec/ft_lst_to_str.c                         */
/* -------------------------------------------------------------------------- */
int     ft_t_envlen();
char    **ft_t_env_to_enp(t_env **envp);

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/fill_fd.c                            */
/* -------------------------------------------------------------------------- */
int	fill_fd(t_commande_line **stc);

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/ft_exec.c                            */
/* -------------------------------------------------------------------------- */
int     ft_exec(t_commande_line	**s_cmd_line);

int		open_pipe(t_commande_line **cmdl);
void	close_fd_all(t_commande_line **cmdl);
int		open_fd(t_commande_line **cmdl);
char	**env_to_tabtab(t_env **envp);

int		create_heredoc_fd(t_commande_line **cmdl, t_token **cur);
char	*creat_aleatori_name(void);

#endif
