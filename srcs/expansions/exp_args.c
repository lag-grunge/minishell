#include "expansions.h"

void	make_expansions(t_list **args)
{
	int		exp_num;
	t_list	*cur;

	cur = *args;
	while (cur)
	{
		exp_num = variable_expansion(cur);
		cur = cur->next;
	}
	ft_lstdel_empty(args);
	cur = *args;
	while (cur)
	{
		filename_expansion(cur, exp_num);
		cur = cur->next;
	}
}

static int make_red_subs(char **red_word)
{
	int		exp_num;
	t_list	*new_list;
	int 	ret;
	char 	*tmp;

	tmp = ft_strdup(*red_word);
	if (!tmp)
		exit (malloc_err);
	new_list = ft_lstnew(tmp);
	exp_num = variable_expansion(new_list);
	if (!exp_num && new_list)
	{
		filename_expansion(new_list, exp_num);
		ret = (ft_lstsize(new_list) != 1) * syntax_err;
		if (!ret)
		{
			*red_word = ft_strdup(new_list->content);
			if (!*red_word)
				exit(malloc_err);
		}
	}
	else
		ret = syntax_error(syntax_err, tmp, "./minishell: ambigious_redirect");
	ft_lstclear(&new_list, free);
	free(tmp);
	return (ret);
}

int make_all_red_exp(t_redir *red)
{
	t_redir *cur;
	int 	ret;

	cur = red;
	while (cur)
	{
		if (cur->type != red_rh_doc)
		{
			ret = make_red_subs(&cur->word);
			if (ret)
				return (ret);
		}
		cur = cur->next;
	}
	return (0);
}
