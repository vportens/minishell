/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 14:50:47 by viporten          #+#    #+#             */
/*   Updated: 2021/11/03 00:54:27 by laclide          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/includes/libft.h"
# include <stdbool.h>

char							**g_envp;

typedef struct s_exec			t_exec;
typedef struct s_commande_line	t_commande_line;
typedef struct s_token			t_token;
typedef struct s_env			t_env;

typedef enum quote
{
	NONE,
	SINGLE,
	DOUBLE,
	BACKSLASH,
	END
}	e_quote;

typedef enum token
{
	NON,
	ARG,
	BUILTIN,
	OPEN_FILE,
	HERE_DOC,
	LIMITOR,
	CREAT_FILE,
	WRITE_FILE,
	FILE_IN,
	FILE_OUT,
	FILE_OUT_OVER,
	ENDS
}				e_token;

struct		s_exec
{
	char	*path;
	char	**argv;
	char	*file_in;
	char	*file_out;
	int		fd_in;
	int		fd_out;
	t_exec	*next;	
};

struct		s_token
{
	char	*str;
	e_token	type;
	bool	expanded;
	t_token	*next;
};

struct				s_commande_line
{
	char			*string;
	t_token			*first_token;
	char			**envp;
	char			**argv;
	t_commande_line	*next;
};

struct		s_env
{
	char	*str;
	t_env	*next;
};

int		get_next_quote(char	*str, int i);

void	init_type(t_token *new);
void	init_token(t_token *new);
int		is_builtin(char *str);

void	cmdl_add_back(t_commande_line **first, t_commande_line *add_back);
void	token_add_back(t_token **first, t_token *add_back);

int		unclose_quote(char	*str);
e_quote	update_quote_status(char c, e_quote quote);
e_quote	update_quote_succes(t_token *stc, int *i, e_quote quote);
int		pars_cmd_line(t_commande_line **cmd_lst, char *str);

int		is_separator(char c);
int		is_redirection(char c);

int		expend_words(t_commande_line **block);
int		limitor(t_token *stc, char *str);
char	*devellope_limitor(t_token *stc, char *str, int i);
char	*word_will_single(char *str, int *i, char *s1);
char	*word_will_double(char *str, int *i, char *s1);
char	*string_before_env(char *str, char *s1, int *i, int j);
char	*word_will_unquote(t_token **stc, char *str, int *i, char *s1);
char	*string_env(char *str, char *tmp, int *i);
char	*end_word_unquote(char *str, char *s1, int *i, int j);

char	*get_env(int *j, char *str);


char	*copy_fake_env(char *str);
char	*fake_env(int *j, int len_str);
int		len_fake_env(char *str);

void	free_both(char *s1, char *s2);
int		free_cmdl_ret_malloc_error(t_commande_line *str);
int		free_token_ret_malloc_error(t_token *tok);
char	*free_str_ret_null(char *s1);
void	free_split(char **split);

int		get_cmd_line(char *string, t_commande_line **first);

int	split_all_cmdl_string_to_token(t_commande_line **first);

int		organise_arg(t_commande_line **cmd);

int		ft_truestrncmp(char *str, char *to, int n);
void	get_environment(char **env);

#endif
