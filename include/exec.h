/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by rmechety          #+#    #+#             */
/*   Updated: 2021/11/05 11:34:35 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "struct.h"

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/ft_exist.c                           */
/* -------------------------------------------------------------------------- */
int ft_expend(t_commande_line *cmd_line);
int ft_test_exist(t_commande_line *cmd_line);
int ft_exist(t_commande_line *cmd_line);
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
void    ft_no_fork_exec(t_commande_line **cmd_line, char *str);
int     ft_execute_cmd(t_commande_line *cur, pid_t **pid, int *i);
int     ft_exec(t_commande_line	**s_cmd_line, char *str);
#endif
