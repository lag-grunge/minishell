#ifndef MINISHELL_CLEAN_H
#define MINISHELL_CLEAN_H
#include "minishell.h"

void clean_cmd(t_cmd *cmd);
void clean_all(t_stmnt **stmnt);
void clean_env_hash(t_env *env_start);
void del_env_one(t_env *tmp);

#endif
