/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   variable.c										 :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: sdalton <marvin@42.fr>					 +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2022/03/19 13:57:50 by sdalton		   #+#	#+#			 */
/*   Updated: 2022/03/19 13:57:51 by sdalton		  ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "expansions.h"

static int	get_size(char *token)
{
	char	*cur;
	int		exp_num;

	exp_num = 0;
	cur = token;
	while (*cur)
	{
		while (*cur == ' ')
			cur++;
		if (*cur && *cur != ' ')
			exp_num++;
		while (*cur && *cur != ' ')
		{
			if (*cur == '\'' || *cur == '\"')
				cur += quoting(cur);
			else
				cur++;
		}
	}
	if (exp_num)
		return (exp_num);
	return (1);
}

static void	oper_word(t_list *args_list, char *cur, char *token, int s)
{
	char	*tmp;

	tmp = ft_substr(token, s, cur - token - s);
	if (!tmp)
		exit(malloc_err);
	write_word(&args_list, tmp);
}

static int	trim_spaces(char **cur_ptr, char *token)
{
	char	*cur;

	cur = *cur_ptr;
	while (*cur == ' ')
		cur++;
	*cur_ptr = cur;
	return (cur - token);
}

static void	expan_list(t_list *args_list, char *token)
{
	char	*cur;
	int		s;

	cur = token;
	s = trim_spaces(&cur, token);
	if (!*cur)
		oper_word(args_list, cur, token, s);
	while (*cur)
	{
		while (*cur && *cur != ' ')
		{
			if (*cur == '\'' || *cur == '\"')
				cur += quoting(cur);
			else
				cur++;
		}
		if (*cur == ' ')
		{
			oper_word(args_list, cur, token, s);
			args_list = args_list->next;
			s = trim_spaces(&cur, token);
		}
	}
	if (cur - token - s > 0)
		oper_word(args_list, cur, token, s);
}

void	variable_expansion(t_list *args_list)
{
	int		exp_num;
	char	*token;

	token = ft_strdup(args_list->content);
	exec_expansion(&token);
	exp_num = get_size(token);
	if (exp_num > 1)
		args_list = ft_lstins_few_empty(args_list, exp_num - 1);
	if (ft_strncmp(token, args_list->content, ft_strlen(token) + 1))
		expan_list(args_list, token);
	free(token);
}
