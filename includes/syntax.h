/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 18:37:55 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 18:38:00 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SYNTAX_H
# define SYNTAX_H
# include "minishell.h"
# include "error.h"

t_token	type(char *cur);
int		ft_isoperator(char *s);

int		expect(t_token t, char ***cur, char *module);
int		accept(t_token t, char ***cur);

char	*ft_name(char *start);
char	*ft_number(char *start);

char	*ft_meta(char *read_line, int *nt, char **unexp);
int		ft_ismeta(int c);

char	*word(char *read_line, int *nt);

char	**get_tokens(char *read_line, int *empty);

int		quoting(char *read_line);
char	*quote_removal(char *token);

#endif
