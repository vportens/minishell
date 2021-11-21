/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   word_will_unquote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 01:27:37 by laclide           #+#    #+#             */
/*   Updated: 2021/11/21 18:40:58 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*free_split_ret_str(char **split, char *str)
{
	free_split(split);
	return (str);
}

char	*new_token_env(t_token **stc, char **split, int i)
{
	t_token	*next;
	t_token	*new;

	if ((*stc))
		next = (*stc)->next;
	while (split[i])
	{
		new = malloc(sizeof(t_token));
		if (new == NULL)
			return (free_split_ret_str(split, NULL));
		init_token(new);
		new->type = ARG;
		new->str = ft_strdup(split[i]);
		if (new->str == NULL)
			if (new)
				return (free_split_token(split, new));
		if ((*stc))
			new->next = next;
		(*stc)->next = new;
		(*stc) = (*stc)->next;
		i++;
	}
	free_split(split);
	return (new->str);
}

static char	*if_no_env(char *str, int *i, char *s1)
{
	char	*new;
	char	*join;
	int		start;

	start = *i;
	while (str[(*i)] && str[(*i)] != '\'' && str[(*i)] != '"'
		&& str[(*i)] != '$')
		(*i)++;
	new = malloc(sizeof(char) * ((*i) - start + 1));
	if (new == NULL)
		return (free_str_ret_null(s1));
	new = ft_strncpy(new, str + start, ((*i) - start));
	join = ft_strjoin(s1, new);
	free_both(s1, new);
	return (join);
}

static char	*if_env(t_token **stc, char *str, char *s1, int *i)
{
	char	*env;
	char	**split;
	char	*join;

	env = string_env(str, s1, i);
	if (env == NULL)
		return (free_str_ret_null(s1));
	split = ft_strsplit(env, ' ');
	free(env);
	if (split == NULL)
		return (free_str_ret_null(s1));
	join = ft_strjoin(s1, split[0]);
	if (s1 == NULL && split[0] == NULL)
	{
		join = malloc(sizeof(char));
		join[0] = '\0';
	}
	free(s1);
	if (split[0] == NULL || split[1] == NULL)
		return (free_split_ret_str(split, join));
	(*stc)->str = join;
	return (new_token_env(stc, split, 1));
}

char	*word_will_unquote(t_token **stc, char *str, int *cur, char *s1)
{
	while (str[*cur] && str[*cur] != '\'' && str[*cur] != '"')
	{
		if (str[*cur] != '$')
		{
			s1 = if_no_env(str, cur, s1);
			if (s1 == NULL)
				return (NULL);
		}
		else if (str[*cur] && str[*cur] == '$')
		{
			s1 = if_env(stc, str, s1, cur);
			if (s1 == NULL)
			{
				return (NULL);
			}
		}
	}
	return (s1);
}
