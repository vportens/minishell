/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:06:59 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/04 19:16:34 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H
# include "define.h"

typedef struct s_exec			t_exec;
typedef struct s_token			t_token;
typedef struct s_commande_line	t_commande_line;
typedef struct s_env			t_env;


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
	int				pipe[2];
	int				pid;
	t_commande_line	*next;
};

struct		s_env
{
	char	*str;
	t_env	*next;
};

#endif
