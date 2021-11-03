/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchristo <lchristo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:37:58 by lchristo          #+#    #+#             */
/*   Updated: 2021/11/02 19:51:29 by lchristo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **ep)
{
  if (ft_init_t_env(ep) == 50)
  {
    ft_clean_envlist(get_adress_env());
    return (-1);
  }
  // ft_built_in_env();
  ft_built_in_echo(&av[2]);
  if (ft_built_in_pwd() == 50)
    return (-1);
  //ft_built_in_export();
  //ft_built_in_show_export();
  //ft_built_in_unset();
  //ft_built_in_show_export();
  //ft_delete_env("caca=1");
  //ft_clean_env();
  return (0);
}
