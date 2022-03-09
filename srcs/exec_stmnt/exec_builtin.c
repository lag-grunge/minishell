#include "exec_stmnt.h"
#include "syntax.h"
#include "builtin.h"

int fake_isbuiltin(t_cmd *cmd)
{
	int ret;

	ret = 1;
	if (!ft_strncmp(cmd->args->content, "export", 256))
	{
//		printf("export\n");
	}
	else if (!ft_strncmp(cmd->args->content, "exit", 256))
	{
//		printf("export\n");
	}
	else if (!ft_strncmp(cmd->args->content, "echo", 256))
	{

	}
	else
		ret = 0;
	return (ret);
}



int fake_exec_builtin(t_cmd *cmd)
{
	(void)cmd;
	int		ret;

    ret = 0;
	if (!ft_strncmp(cmd->args->content, "export", 256))
	{
		ret = export(cmd->args->next);
//		printf("export\n");
	}
	else if (!ft_strncmp(cmd->args->content, "exit", 256))
	{
		exit_shell(cmd->args->next, 1);
		ret = 1;
	}
	else if (!ft_strncmp(cmd->args->content, "echo", 256))
		echo(cmd->args->next);
	return (ret);
}

