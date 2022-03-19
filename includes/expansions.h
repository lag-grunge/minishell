/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansions.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:37:11 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 18:37:13 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSIONS_H
# define EXPANSIONS_H
# include "minishell.h"
# include "environment.h"
# include "parser.h"
# include "syntax.h"

void	variable_expansion(t_list *args_list);
void	filename_expansion(t_list *args_list);
int		match(char *d_name, char *token);
void	exec_expansion(char **token);
int		make_all_red_exp(t_redir *red);
void	make_expansions(t_list **args);

char	*make_substitution(char **tokens, char *dollar, \
							char *end_var, char *value);
#endif
