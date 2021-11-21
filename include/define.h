/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:07:15 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 22:11:29 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

typedef enum quote
{
	NONE,
	SINGLE,
	DOUBLE,
	BACKSLASH,
	END
}	t_quote;

typedef enum mod
{
	GET,
	DELETE,
	FREE,
	ADD
}			t_mod;

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
}				t_e_token;

#endif