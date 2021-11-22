/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_built_in_export.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: viporten <viporten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 13:58:15 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/21 22:21:19 by viporten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

void	ft_built_in_show_export(void)
{
	t_env	**env;

	env = get_adress_env();
	ft_show_export(env);
}

int	ft_export_is_incorrect(char *s)
{
	int	i;

	i = 1;
	if ((ft_is_alpha(s[0]) && s[0] != '_'))
		return (1);
	while (s[i] && s[i] != '=')
	{
		if ((ft_is_alpha_num(s[i]) && s[i] != '_'))
		{
			if (!(s[i] == '+' && s[i + 1] == '='))
				return (1);
		}
		i++;
	}
	return (0);
}

int	ft_built_in_export(char **str)
{
	int	i;

	i = 1;
	g_exit_status = 0;
	if (*(str + 1) == NULL)
	{
		ft_built_in_show_export();
		return (0);
	}
	while (str[i] != NULL)
	{
		if (ft_export_is_incorrect(str[i]))
		{
			g_exit_status = 1;
			printf("minishell: export: '%s': not a valid identifier\n", str[i]);
		}
		else if (ft_singletone(str[i], ADD) == 50)
			return (50);
		i++;
	}
	return (0);
}

void	ft_show_export(t_env **env)
{
	t_env	*cur;
	int		len;

	cur = *env;
	while (cur)
	{
		len = ft_get_lenkey(cur->str);
		if (cur->declare == 1)
			printf("declare -x %.*s", len, cur->str);
		else
			printf("export %.*s", len, cur->str);
		if (len < (int)ft_strlen(cur->str))
			printf("=\"%s\"", cur->str + len + 1);
		printf("\n");
		cur = cur->next;
	}
}
