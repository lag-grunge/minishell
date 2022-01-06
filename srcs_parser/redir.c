#include "syntax.h"
#include "parser.h"

static t_redir *ft_redir_new(void)
{
	t_redir	*red;

	red = malloc(sizeof(t_redir) * 1);
	if (!red)
		return (NULL);
	red->type = 0;
	red->word = NULL;
	red->next = NULL;
	return (red);
}

static t_redir	*add_redir_item(t_redir **red)
{
	t_redir	*r;

	r = *red;
	if (!r)
	{
		*red = ft_redir_new();
		return (*red);
	}
	while (r->next)
		r = r->next;
	r->next = ft_redir_new();
	return (r->next);
}

static int write_redir(t_redir **redirect, char **tokens)
{
	char		*red_token;
	char 		*wrd_token;
	t_ctrls		red_type;
	t_redir		*red;

	red = add_redir_item(redirect);
	if (!red)
		return (malloc_err);
	red_token = tokens[-2];
	wrd_token = tokens[-1];
	red_type = ft_isoperator(red_token);
	if (red_type == ct_ltlt)
		red->type = red_rh_doc;
	else if (red_type == ct_lt)
		red->type = red_rifile;
	else if (red_type == ct_gt)
		red->type = red_wofile;
	else if (red_type == ct_gtgt)
		red->type = red_aofile;
	red->word = ft_strdup(wrd_token);
	if (!red->word)
		return (malloc_err);
	return (0);
}

int ft_redir(t_redir **red, char ***tokens)
{
	if (expect(wrd, tokens, "ft_redir"))
		return (syntax_error(syntax_err, **tokens, "ft_redir"));
	if (red)
		return (write_redir(red, *tokens));
	return (0);
}
