#ifndef MINISHELL_PARSER_H
#define MINISHELL_PARSER_H
# include "syntax.h"
# include "minishell.h"

int ft_redir(t_redir **red, char ***tokens);
int ft_subshell(t_stmnt **stmnt, t_redir **red, char **tokens);
int ft_cmd(t_stmnt **stmnt, char **tokens, char **lim_token);
char **close_bracket(char **tokens, char **lim_token);
int check_brackets(char **tokens);
int ft_parser(t_stmnt **stmnt, char **tokens, char **lim_token);
int ft_preparser(char **tokens, char **lim_token);

#endif //MINISHELL_PARSER_H
