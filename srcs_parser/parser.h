#ifndef MINISHELL_PARSER_H
#define MINISHELL_PARSER_H
# include "syntax.h"
# include "minishell.h"

//t_stmnt *ft_stmnt_new(void);
//t_cmd *ft_cmd_new(void);
//t_redir *ft_redir_new(void);

int ft_redir(t_redir **red, char ***tokens);
int ft_subshell(t_stmnt **stmnt, t_redir **red, char **tokens);
int ft_cmd(t_stmnt **stmnt, char **tokens, char **lim_token);
char **close_bracket(char **tokens);
int ft_parser(t_stmnt **stmnt, char **tokens, char **lim_token);

#endif //MINISHELL_PARSER_H
