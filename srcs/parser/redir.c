#include "../../includes/syntax.h"
#include "../../includes/parser.h"
#include "expansions.h"
#include "environment.h"

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

static int write_redir_word(char **word, char **tokens, char *pwd)
{
	char	**spl_token;

	spl_token = variable_expansion(tokens, g_data.env);
	filename_expansion(word, pwd, spl_token);
	clean_split(spl_token, ft_spllen(spl_token));
	return (0);
}

static int write_redir(t_redir **redirect, char **tokens, char *pwd)
{
	char		*red_token;
	char 		*wrd_token;
	t_ctrls		red_type;
	t_redir		*red;

	red = add_redir_item(redirect);
	if (!red)
		exit (malloc_err);
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
	write_redir_word(&red->word, &wrd_token, pwd);
	return (0);
}

int ft_redir(t_redir **red, char ***tokens)
{
	char	**spl_tokens;
	char	*pwd;
	int 	ret;

	if (expect(wrd, tokens, "ft_redir"))
		return (syntax_error(syntax_err, **tokens, "ft_redir"));
	spl_tokens = variable_expansion(*tokens - 1, g_data.env);
	if (ft_spllen(spl_tokens) > 1)
	{
		clean_split(spl_tokens, ft_spllen(spl_tokens));
		return (syntax_error(syntax_err, (*tokens)[-1], "ft_redir: ambigious redirect"));
	}
	pwd = get_key_value(g_data.env, "PWD");
	ret = count_filename_expansion(pwd, spl_tokens);
	if (red && ret == 1)
		ret = write_redir(red, &(*tokens)[-1], pwd);
	else if (ret > 1)
		ret = syntax_error(syntax_err, (*tokens)[-1], "ft_redir: ambigious redirect");
	else if (!red)
		ret = 0;
	clean_split(spl_tokens, ft_spllen(spl_tokens));
	free(pwd);
	return (ret);
}