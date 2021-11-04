/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prototypes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmechety <rmechety@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/17 12:52:24 by rmechety          #+#    #+#             */
/*   Updated: 2021/10/19 15:08:54 by rmechety         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

#include "struct.h"

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/fill_fd.c                            */
/* -------------------------------------------------------------------------- */
int	fill_fd(t_commande_line **stc);

/* -------------------------------------------------------------------------- */
/*                           FILE = exec/ft_exec.c                            */
/* -------------------------------------------------------------------------- */
int     ft_exec(t_commande_line	**cmd_line, char *str);


#endif
