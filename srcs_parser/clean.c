#include "clean.h"

static void free_if_exist(void *s, void (*func)(void *))
{
	if (s)
		func(s);
}

void	clean_redir(void *ptr)
{
	t_redir *red;
	t_redir *tmp;

	red = ptr;
	while (red)
	{
		tmp = red;
		red = red->next;
		free(tmp);
	}
}

void clean_cmd(t_cmd *cmd)
{
	if (cmd->args)
		clean_split(cmd->args, ft_spllen(cmd->args));
	free_if_exist(cmd->redir, clean_redir);
	free(cmd);
}

