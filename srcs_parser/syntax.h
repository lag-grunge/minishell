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

int ft_bin(t_cmd *cmd, char ***tokens);
int ft_args(char ***tokens);
int ft_redir(t_cmd *cmd, char ***tokens);
int ft_oper(char ***tokens);
int ft_pipe(char ***tokens);

#endif
