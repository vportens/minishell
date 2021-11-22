/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by viporten          #+#    #+#             */
/*   Updated: 2021/11/22 00:39:44 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "struct.h"

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/ft_exist.c                           */
/* -------------------------------------------------------------------------- */
char	*get_acces(char *str, char *path);
int		try_acces(char *str, char *path);
char	*get_bin_argv_zero(char *str, char *path, int i);

/* -------------------------------------------------------------------------- */
/*                        FILE = exec/ft_lst_to_str.c                         */
/* -------------------------------------------------------------------------- */
int		ft_t_envlen(void);
char	**ft_t_env_to_enp(t_env **envp);

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/fill_fd.c                            */
/* -------------------------------------------------------------------------- */
int		fill_fd(t_commande_line **stc);

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/ft_exec.c                            */
/* -------------------------------------------------------------------------- */
int		ft_exec(t_commande_line	**s_cmd_line);

int		open_pipe(t_commande_line **cmdl);
void	close_fd_all(t_commande_line **cmdl);
int		open_fd(t_commande_line **cmdl);
char	**env_to_tabtab(t_env **envp);

int		create_heredoc_fd(t_commande_line **cmdl, t_token **cur);
char	*creat_aleatori_name(void);

void	free_fd_all_exit_malloc_error(t_commande_line **first);
void	free_str_fd_exit_malloc_error(char **str,
			t_commande_line **first);
void	free_str_exit_fd_error(char **str);
void	free_str_fd_all_env_pid_exit(t_commande_line **cmd,
			pid_t *pid, char **str);
void	free_file_name(char *file_name);

int		wait_pid(t_commande_line **cmdl, pid_t *pid);
int		no_forking(t_commande_line **cmdl, pid_t *pid);
int		exec_builtin(char **str, t_commande_line **cmdl,
			t_commande_line **first, pid_t *pid);
void	signal_cmd_2(int sig);
char	*free_split_ret_null(char **split_path);

#endif
