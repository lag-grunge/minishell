#ifndef MINISHELL_PARSER_H
#define MINISHELL_PARSER_H
# include "minishell.h"
# include "syntax.h"
# include "clean.h"

int ft_redir(t_redir **red, char ***tokens);
int ft_parenthesis(t_stmnt **stmnt, t_redir **red, char **tokens);
int ft_cmd(t_stmnt **stmnt, char **tokens, char **lim_token);
int		write_word(t_list **cur, char *tokens);
void	rewrite_redir(char **red_word, char *tokens);
char **close_bracket(char **tokens, char **lim_token, int direction);
int check_brackets(char **tokens, char **lim_token);
int ft_stmnt(t_stmnt **stmnt, char **tokens, char **lim_token);
int ft_parser(t_stmnt **stmnt, char **tokens, char **lim_token);
int ft_preparser(char **tokens, char **lim_token);

#endif //MINISHELL_PARSER_H
