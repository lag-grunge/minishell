#ifndef MINISHELL_PARSER_H
#define MINISHELL_PARSER_H
# include "syntax.h"
# include "minishell.h"

t_stmnt *ft_stmnt_new(void);
t_cmd *ft_cmd_new(void);
t_redir *ft_redir_new(void);
void add_oper(t_stmnt **stmnt, t_cmd *cmd, char ***tokens);


void ft_cmd(t_cmd **cmd, t_redir **red, char ***tokens);
int ft_parser(t_stmnt **stmnt, char **tokens);
char **get_tokens(char *read_line);


#endif //MINISHELL_PARSER_H
