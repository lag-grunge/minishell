#include "clean.h"

static void free_if_exist(void *s, void (*func)(void *))
{
	if (s)
		func(s);
}

void	clean_redir(void *ptr)
{
	t_redir *red;

	red = ptr;
	free_if_exist(red->infile, free);
	free_if_exist(red->lim, free);
	free_if_exist(red->outfile, free);
	free(red);
}

void clean_cmd(t_cmd *cmd)
{
	if (cmd->args)
		clean_split(cmd->args, ft_spllen(cmd->args));
	free_if_exist(cmd->redir, clean_redir);
	free(cmd);
}

