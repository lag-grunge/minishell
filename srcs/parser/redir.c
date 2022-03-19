/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 13:41:35 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/19 13:41:37 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/syntax.h"
#include "../../includes/parser.h"
#include "expansions.h"
#include "environment.h"

static	t_redir	*ft_redir_new(void)
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

void	rewrite_redir(char **red_word, char *tokens)
{
	char	*tmp;

	tmp = ft_strdup(tokens);
	if (!tmp)
		exit(malloc_err);
	if (*red_word)
		free(*red_word);
	*red_word = tmp;
}

static void	write_redir(t_redir **redirect, char **tokens)
{
	t_ctrls		red_type;
	t_redir		*red;

	red = add_redir_item(redirect);
	if (!red)
		exit (malloc_err);
	red_type = ft_isoperator(tokens[-1]);
	if (red_type == ct_ltlt)
		red->type = red_rh_doc;
	else if (red_type == ct_lt)
		red->type = red_rifile;
	else if (red_type == ct_gt)
		red->type = red_wofile;
	else if (red_type == ct_gtgt)
		red->type = red_aofile;
	else if (red_type == ct_egt)
		red->type = red_eofile;
	else if (red_type == ct_egtgt)
		red->type = red_aefile;
	red->word = ft_strdup(tokens[0]);
	if (!red->word)
		exit(malloc_err);
}

int	ft_redir(t_redir **red, char ***tokens)
{
	int	ret;

	ret = 0;
	if (!**tokens)
		return (syntax_error(syntax_err, **tokens, \
		"minishell: redir: unexpected newline"));
	if (expect(wrd, tokens, "redir"))
		return (syntax_err);
	if (red)
		write_redir(red, *tokens - 1);
	return (0);
}
