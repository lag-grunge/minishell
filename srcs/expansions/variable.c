#include "expansions.h"

static int get_size(char *token)
{
	char *cur;
	int	exp_num;

	exp_num = 0;
	cur = token;
	while (*cur)
	{
		if (*cur == '\'' || *cur == '\"')
			cur += quoting(cur);
		else if (*cur == ' ')
		{
			exp_num++;
			cur++;
		}
		else
			cur++;
	}
	return (exp_num);
}

static void write_content(t_list *args_list, char *cur, char *token, int s)
{
	if (args_list->content)
		free(args_list->content);
	args_list->content = ft_substr(token, s, cur - token - s);
	if (!args_list->content)
		exit(malloc_err);
}

static int oper_word(t_list *args_list, char **cur_ptr, char *token, int s)
{
	char *cur;

	cur = *cur_ptr;
	if (cur != token)
		write_content(args_list, cur, token, s);
	while (*cur == ' ')
		cur++;
	return ((int)(cur - token));
}

static void expan_list(t_list *args_list, char *token)
{
	char *cur;
	int	s;

	cur = token;
	s = 0;
	while (*cur)
	{
		if (*cur == '\'' || *cur == '\"')
			cur += quoting(cur);
		else if (*cur == ' ')
		{
			s = oper_word(args_list, &cur, token, s);
			args_list = args_list->next;
		}
		else
			cur++;
	}
	if (cur - token - s > 0)
		write_content(args_list, cur, token, s);
	else if (cur == token)
		args_list->content = ft_strdup("");
}

int variable_expansion(t_list *args_list)
{
	int	exp_num;
	char *token;

	token = ft_strdup(args_list->content);
	exec_expansion(&token);
	exp_num = get_size(token);
	if (exp_num)
		ft_lstins_few_empty(args_list, exp_num);
	expan_list(args_list, token);
	free(token);
	return (exp_num);
}