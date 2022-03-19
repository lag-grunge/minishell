/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:36:36 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 18:36:45 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLEAN_H
# define CLEAN_H
# include "minishell.h"

void	clean_cmd(t_cmd *cmd);
void	clean_all(t_stmnt **stmnt);
void	clean_env_hash(t_env *env_start);
void	del_env_one(t_env *tmp);

#endif
