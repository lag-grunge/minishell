/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biltins.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fphlox <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 02:45:08 by fphlox            #+#    #+#             */
/*   Updated: 2022/03/15 02:45:09 by fphlox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BILTINS_H
# define BILTINS_H
# include "minishell.h"
# include "environment.h"

int		ft_exit(t_list *orgs);
int		ft_env(t_list *orgs, t_env *local_env);
int		ft_unset(t_list *orgs, t_env *local_env);
int		ft_export(t_list *orgs, t_env *local_env);
int		ft_pwd(t_list *orgs, t_env *local_env);
int		ft_cd(t_list *orgs, t_env *local_env);
int		ft_echo(t_list *orgs);
int		ft_is_bilt(t_list *orgs);
int		ft_bilt_start(t_list *orgs);
void	er_mes(char *start, char *content, char *end);

#endif
