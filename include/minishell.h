/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:50:47 by viporten          #+#    #+#             */
/*   Updated: 2021/11/22 17:12:55 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../srcs/libft/includes/libft.h"
# include <stdbool.h>
# include "parsing.h"
# include "exec.h"
# include "builtin.h"
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>

void	signal_cmd(int sig);
int		print_exit_free_env_all(t_commande_line **cmd);

int		free_all_env_str_ret_malloc_error(t_commande_line **cmd, char *str);

int		free_all_error(t_commande_line **cmd, char *str, int error);

void	free_end(t_commande_line **cmd, char *str);

void	free_token(t_commande_line **cmd_line);
int		free_str_all_ret_malloc_error(t_commande_line **cmd, char *str);
void	error_str(void);
int		free_all(t_commande_line **cmd_line);
#endif
