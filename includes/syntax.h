#ifndef MINISHELL_SYNTAX_H
#define MINISHELL_SYNTAX_H
#include "minishell.h"

t_token	type(char *cur);
int expect(t_token t, char ***cur, char *module);

char *ft_name(char *start);
int syntax_error(int ret, char *token, char *module);
int accept(t_token t, char ***cur);


char **get_tokens(char *read_line, int *empty);
char *ft_meta(char *read_line, int *nt, char **unexp);
char	*word(char *read_line, int *nt);
int		ft_ismeta(int c);
int 	ft_isoperator(char *s);
int		quoting(char *read_line);

#endif
