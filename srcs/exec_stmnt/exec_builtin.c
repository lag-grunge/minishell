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
	else
		ret = 0;
	return (ret);
}

int fake_export(t_list *args)
{
	char *key, *val;
	char *assign;
	char *argv;

	argv = NULL;
	if (args->next)
		argv = ft_strdup(args->next->content);
	if (!argv) {
		print_env(g_data.env);
		return (0);
	}
	if (ft_strchr(argv, '?'))
		return (1);
	assign = ft_strchr(argv, '=');
	if (assign)
	{
		key = ft_substr(argv, 0, assign - argv);
		val = ft_substr(argv, assign - argv + 1, ft_strlen(argv));
		if (!key || !val)
			exit(malloc_err);
		set_value(&g_data.env, key, val);
		free(key);
	}
	else
	{
		key = ft_substr(argv, 0, ft_strlen(argv));
		set_value(&g_data.env, key, NULL);
		free(key);
	}
	return (0);
}


int fake_exec_builtin(t_cmd *cmd)
{
	(void)cmd;
	int		ret;

    ret = 0;
	if (!ft_strncmp(cmd->args->content, "export", 256))
	{
		ret = fake_export(cmd->args);
//		printf("export\n");
	}
	else if (!ft_strncmp(cmd->args->content, "exit", 256))
		exit_shell(1);
	return (ret);
}

