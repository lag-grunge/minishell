#ifndef MINISHELL_SYNTAX_H
#define MINISHELL_SYNTAX_H
#include "minishell.h"
int		ft_isoperator(char *s, int len);

typedef enum e_token {lg, wrd, op, pp, lb, rb} t_token;
t_token	type(char *cur);
int expect(t_token t, char ***cur);
char **nextsym(char **cur);
int	 error();
int accept(t_token t, char ***cur);

void ft_word(char **args, char ***tokens);
void ft_redir(t_redir *red, char ***tokens);
int ft_oper(char ***tokens);
int ft_pipe(char ***tokens);

#endif
