/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:06:42 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 22:19:39 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "struct.h"

int			get_next_quote(char	*str, int i);

void		init_type(t_token *new);
void		init_token(t_token *new);
int			ft_is_builtin(char *str);

void		cmdl_add_back(t_commande_line **first, t_commande_line *add_back);
void		token_add_back(t_token **first, t_token *add_back);
int			len_cmd(t_commande_line *cmd);

int			unclose_quote(char	*str);
t_quote		update_quote_status(char c, t_quote quote);
t_quote		update_quote_succes(t_token *stc, int *i, t_quote quote, char **s1);
int			pars_cmd_line(t_commande_line **cmd_lst, char *str);

int			is_separator(char c);
int			is_redirection(char c);

int			expend_words(t_commande_line **block);
int			limitor(t_token *stc, char *str);
int			is_type_file(t_e_token type);
char		*devellope_limitor(t_token *stc, char *str, int i);
char		*word_will_single(char *str, int *i, char *s1);
char		*word_will_double(char *str, int *i, char *s1);
char		*string_before_env(char *str, char *s1, int *i, int j);
char		*word_will_unquote(t_token **stc, char *str, int *i, char *s1);
char		*string_env(char *str, char *tmp, int *i);
char		*end_word_unquote(char *str, char *s1, int *i, int j);

int			ret_file_without_obj(t_e_token type);
int			is_type_file(t_e_token type);
int			end_modif_two(char *str, t_token **stc, char *s1);
char		*init_str(char **str, char *duplica, int *cur, char **s1);
t_e_token	cp_type_change_file(t_e_token type, int *file);
int			ret_error_file_without_file(t_commande_line *cur_b);
t_e_token	change_type_file(t_e_token type, int *file);

char		*get_env(int *j, char *str);

char		*copy_fake_env(char *str);
char		*fake_env(int *j, int len_str);
int			len_fake_env(char *str);

int			free_all(t_commande_line **cmd_line);
void		free_both(char *s1, char *s2);
int			free_cmdl_ret_malloc_error(t_commande_line *str);
int			free_token_ret_malloc_error(t_token *tok);
char		*free_str_ret_null(char *s1);
void		free_split(char **split);
char		*free_split_token(char **split, t_token *tok);
int			free_str_ret_malloc_error(char *str);

char		*free_split_ret_str(char **split, char *str);

int			get_cmd_line(char *string, t_commande_line **first);

int			split_all_cmdl_string_to_token(t_commande_line **first);

int			organise_arg(t_commande_line **cmd);

int			ft_strncmp(char *str, char *to, int n);
void		get_environment(char **env);

#endif
