/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 21:49:59 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/18 21:52:48 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

void	make_expansions(t_list **args)
{
	t_list	*cur;
	t_list	*next;

	cur = *args;
	while (cur)
	{
		variable_expansion(cur);
		cur = cur->next;
	}
	ft_lstdel_empty(args);
	cur = *args;
	while (cur)
	{
		next = cur->next;
		filename_expansion(cur);
		cur = next;
	}
}

static int	make_red_subs(char **red_word)
{
	t_list	*new_list;
	int		ret;
	char	*tmp;

	tmp = ft_strdup(*red_word);
	if (!tmp)
		exit (malloc_err);
	new_list = ft_lstnew(tmp);
	variable_expansion(new_list);
	ft_lstdel_empty(&new_list);
	if (ft_lstsize(new_list) == 0)
		return (syntax_error(syntax_err, NULL, \
					"./minishell: ambigious_redirect"));
	else
	{
		filename_expansion(new_list);
		ret = 0;
		if (ft_lstsize(new_list) == 1)
			rewrite_redir(red_word, new_list->content);
		else
			ret = syntax_error(syntax_err, NULL, \
					"./minishell: ambigious_redirect");
		ft_lstclear(&new_list, free);
		return (ret);
	}
}

int	make_all_red_exp(t_redir *red)
{
	t_redir	*cur;
	int		ret;

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
