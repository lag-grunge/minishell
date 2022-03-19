/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:37:23 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 18:37:26 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H
# include "minishell.h"
# include "syntax.h"
# include "clean.h"

int		ft_redir(t_redir **red, char ***tokens);
int		ft_parenthesis(t_stmnt **stmnt, t_redir **red, char **tokens);
int		ft_cmd(t_stmnt **stmnt, char **tokens, char **lim_token);
int		write_word(t_list **cur, char *token);
void	rewrite_redir(char **red_word, char *tokens);
char	**close_bracket(char **tokens, char **lim_token, int direction);
int		check_brackets(char **tokens, char **lim_token);
int		ft_stmnt(t_stmnt **stmnt, char **tokens, char **lim_token);
int		ft_parser(t_stmnt **stmnt, char **tokens, char **lim_token);
int		ft_preparser(char **tokens, char **lim_token);
t_stmnt	*ft_stmnt_new(void);
int		last_stmnt(t_stmnt **stmnt, char **tokens, char **lim_token);

#endif
