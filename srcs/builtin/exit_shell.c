#include "minishell.h"
#include "clean.h"
#include "environment.h"
#include "syntax.h"


int not_numeric_arguments(char *builtin, char *arg)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(builtin, STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": not numeric argument", STDERR_FILENO);
	return (1);
}

void clean_env_type_and_exit(int ret, int type)
{
	clean_env_hash(g_data.env);
	if (!type)
		ft_putendl_fd("\033[Aminishell> exit", STDERR_FILENO);
	else
		ft_putendl_fd("exit", STDERR_FILENO);
	exit(ret);
}

void exit_shell(t_list *args_list, int type)
{
	int ret;
	char *tmp;

	if (args_list && ft_lstsize(args_list) > 1)
	{
		builtin_too_many_arguments_error("exit");
		return ;
	}
	if (args_list && args_list->content)
	{
		if (*ft_number(args_list->content) == 0)
			ret = ft_atoi(args_list->content);
		else
		{
			not_numeric_arguments("exit", args_list->content);
			ret = 255;
		}
	}
	else
	{
		tmp = get_value(g_data.env, "last_status");
		ret = ft_atoi(tmp);
		free(tmp);
	}
	clean_env_type_and_exit(ret, type);
}
