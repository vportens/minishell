/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by viporten          #+#    #+#             */
/*   Updated: 2021/11/22 00:39:32 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

# include "struct.h"

/* -------------------------------------------------------------------------- */
/*                     FILE = built_in/ft_built_in_pwd.c                      */
/* -------------------------------------------------------------------------- */
int		ft_built_in_pwd(char **str);
int		ft_built_in_pwd_fd(char **str, int fd);

/* -------------------------------------------------------------------------- */
/*                     FILE = built_in/ft_built_in_echo.c                     */
/* -------------------------------------------------------------------------- */
int		ft_check_n(char **str);
int		ft_built_in_echo(char **str);
int		ft_built_in_echo_fd(char **str, int fd);
void	ft_built_in_show_env_fd(t_env **env, int fd);
int		ft_built_in_env_fd(char **str, int fd);

/* -------------------------------------------------------------------------- */
/*                     FILE = built_in/ft_built_in_env.c                      */
/* -------------------------------------------------------------------------- */
int		ft_built_in_env(char **str);
int		ft_built_in_env_fd(char **str, int fd);
int		ft_is_equal(char *str);
void	ft_built_in_show_env(t_env **env);
void	ft_built_in_show_env_fd(t_env **env, int fd);
char	*ft_get_str(char *str);
char	*ft_get_env(char *str);

/* -------------------------------------------------------------------------- */
/*                      FILE = built_in/ft_delete_key.c                       */
/* -------------------------------------------------------------------------- */
int		ft_delete_env(char *str);
void	ft_delete_env_call(t_env **env, char *key);

/* -------------------------------------------------------------------------- */
/*                    FILE = built_in/ft_env_singletone.c                     */
/* -------------------------------------------------------------------------- */
int		ft_get_lenkey(char *env);
int		ft_singletone(char *str, int mode);

/* -------------------------------------------------------------------------- */
/*                       FILE = built_in/ft_built_in.c                        */
/* -------------------------------------------------------------------------- */
int		ft_exec_builtin(char *str, char **args,
			t_commande_line **first, pid_t *pid);

/* -------------------------------------------------------------------------- */
/*                       FILE = built_in/ft_add_value.c                       */
/* -------------------------------------------------------------------------- */
int		ft_add_env(char *str);
int		ft_add_value_to_env(t_env **env_list, char *env, int declare);

/* -------------------------------------------------------------------------- */
/*                      FILE = built_in/ft_built_in_cd.c                      */
/* -------------------------------------------------------------------------- */
int		ft_built_in_cd(char **str);
int		ft_built_in_cd_fd(char **str, int fd);

/* -------------------------------------------------------------------------- */
/*                      FILE = built_in/ft_push_front.c                       */
/* -------------------------------------------------------------------------- */
int		ft_push_front(char *env, t_env **begin_lst, int declare);
int		ft_exec_bd_fd(char *str, char **args,
			t_commande_line **first, pid_t *pid);

/* -------------------------------------------------------------------------- */
/*                    FILE = built_in/ft_built_in_export.c                    */
/* -------------------------------------------------------------------------- */
void	ft_built_in_show_export(void);
void	ft_built_in_show_export_fd(int fd);
int		ft_built_in_export(char **str);
int		ft_built_in_export_fd(char **str, int fd);
void	ft_show_export(t_env **env);
int		ft_built_in_export_fd(char **str, int fd);
int		ft_export_is_incorrect(char *s);
char	*ft_final_add(char *env);

/* -------------------------------------------------------------------------- */
/*                     FILE = built_in/ft_gestion_error.c                     */
/* -------------------------------------------------------------------------- */
int		ft_print_error(char *str1, char *str2);

/* -------------------------------------------------------------------------- */
/*                       FILE = built_in/ft_init_env.c                        */
/* -------------------------------------------------------------------------- */
t_env	**get_adress_env(void);
int		ft_init_t_env(char **env);

/* -------------------------------------------------------------------------- */
/*                       FILE = built_in/ft_free_env.c                        */
/* -------------------------------------------------------------------------- */
void	ft_clean_env(void);
void	ft_clean_envlist(t_env **env);
void	ft_free_env_elem(t_env *env);

/* -------------------------------------------------------------------------- */
/*                       FILE = built_in/ft_get_value.c                       */
/* -------------------------------------------------------------------------- */
char	*ft_get_env(char *str);
char	*ft_get_value_of_env(t_env **env, char *str);
char	*ft_get_str_of_env(t_env **env, char *str);

/* -------------------------------------------------------------------------- */
/*                    FILE = built_in/ft_built_in_unset.c                     */
/* -------------------------------------------------------------------------- */
int		ft_built_in_unset(char **str);
int		ft_built_in_unset_fd(char **str, int fd);
int		ft_equal(char *str);
int		free_in_builin(t_commande_line **first, pid_t *pid, int ret);

#endif
