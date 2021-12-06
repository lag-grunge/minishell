#include "minishell.h"

 t_opers *ft_oper_new(void)
 {
	t_opers *op;

	op = (t_opers *)malloc(sizeof(t_opers));
	return (op);
 }

 t_cmd	*ft_cmd_new(void)
 {
	 t_cmd *cmd;

	 cmd = (t_cmd *)malloc(sizeof(t_cmd));
	 return (cmd);
 }