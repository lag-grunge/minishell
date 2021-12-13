#include "syntax.h"
#include "parser.h"

int ft_pattern(t_cmd *cmd, char ***tokens)
{
	if (accept(lg, tokens))
		return (ft_redir(NULL, tokens);
	else if (accept(wrd, tokens))
		return (ft_args(tokens);
	else if (accept(op, tokens))
		return (ft_oper(tokens);
	else if (accept(pp, tokens))
		return (ft_pipe(tokens);
	else if (accept(lb, tokens))
		return (error());
	else if (accept(rb, tokens))
	{
//		if (subshell)
//			return (-1);
		return (error());
	}

}

void write_args(char **args, char **tokens)
{
	char *args_token;

	args_token = tokens[-1];
	*args = ft_strdup(args_token);
}

void ft_word(char **args, char ***tokens)
{
	if (args)
		write_args(args, *tokens);
}


void write_redir(t_redir *red, char **tokens)
{
	char		*red_token;
	char 		*wrd_token;
	t_topers	red_type;

	red_token = tokens[-2];
	wrd_token = tokens[-1];
	red_type = ft_isoperator(red_token, ft_strlen(red_token));
	if (red_type == ltlt)
	{
		red->in = red_rh_doc;
		red->lim = ft_strdup(wrd_token);
	}
	else if (red_type == lt)
	{
		red->in = red_rifile;
		red->infile = ft_strdup(wrd_token);
	}
	else if (red_type == gt || red_type == gtgt)
	{
		red->outfile = ft_strdup(wrd_token);
		red->out = red_wofile;
		if (red_type == gtgt)
			red->out = red_aofile;
	}
}

void ft_redir(t_redir *red, char ***tokens)
{
	if (!expect(wrd, tokens))
		return (0);
	if (red)
		write_redir(red, *tokens);
}