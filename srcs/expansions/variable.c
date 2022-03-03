#include "expansions.h"

static int get_size(char *token)
{
	char *cur;
	int	exp_num;

	exp_num = 1;
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

static int oper_word(t_list *args_list, char **cur_ptr, char *token, int s)
{
	char *cur;
	char *tmp;

	cur = *cur_ptr;
	if (cur != token) {
		tmp = ft_substr(token, s, cur - token - s);
		if (!tmp)
			exit(malloc_err);
		write_word(&args_list, tmp);
	}
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
		oper_word(args_list, &cur, token, s);
}

void variable_expansion(t_list *args_list)
{
	int	exp_num;
	char *token;

	token = ft_strdup(args_list->content);
	exec_expansion(&token);
	exp_num = get_size(token);
	if (exp_num == 1) {
		if (args_list->content)
			free(args_list->content);
		args_list->content = ft_strdup(token);
	}
	else
	{
		args_list = ft_lstins_few_empty(args_list, exp_num - 1);
		expan_list(args_list, token);
	}
	free(token);
}