#ifndef MINISHELL_PARSER_H
#define MINISHELL_PARSER_H
# include "syntax.h"
# include "minishell.h"
t_opers *ft_oper_new(void);
t_cmd *ft_cmd_new(void);
void add_oper(t_opers **opers, int type, char ***tokens);

typedef enum e_topers {
	op_none,
	op_smpl,
	op_or,
	op_and,
	op_sbsh
} t_topers;

int ft_cmd(t_cmd *cmd, char ***tokens);
int ft_parser(t_opers **opers, char *line);
char **get_tokens(char *read_line);


#endif //MINISHELL_PARSER_H
