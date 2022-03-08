#include "builtin.h"

/* builtin started with first argument */
int echo(t_list *args_list)
{
	int newline;

	newline = 1;
	if (args_list)
	{
		if (!ft_strncmp(args_list->content, "-n", 3))
		{
			newline = 0;
			args_list = args_list->next;
		}
		while (args_list)
		{
			ft_putstr_fd(args_list->content, STDOUT_FILENO);
			args_list = args_list->next;
			if (args_list)
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
	}
	if (newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
	return (0);
}
