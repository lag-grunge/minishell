#include "../../includes/minishell.h"
#include "../../includes/syntax.h"
#include "../../includes/environment.h"
#include "../../includes/clean.h"
#include "expansions.h"

char *oper_dollar(char **tokens, char *dollar, t_env *env)
{
	char *start_var;
	char *end_var;
	char *tmp;
	char *ret;
	char *value;

	start_var = dollar + 1;
	end_var = ft_name(start_var);
	if (end_var == start_var)
		return (dollar + 1);
	tmp = ft_substr(start_var, 0, end_var - start_var);
	if (!tmp)
		exit (malloc_err);
	value = get_key_value(env, tmp);
	free(tmp);
	ret = make_substitution(tokens, dollar, end_var, value);
	free(value);
	return (ret);
}

static void exec_expansion(char **token, t_env *env)
{
	char *cur;

	cur = *token;
	while (*cur)
	{
		if (*cur == '$')
			cur = oper_dollar(token, cur, env);
		else if (*cur == '\'')
			cur += quoting(cur);
		else
			cur++;
	}
}

static int get_size(char *token)
{
	char *cur;
	int	spl_num;

	spl_num = 1;
	cur = token;
	while (*cur)
	{
		if (*cur == '\'' || *cur == '\"')
			cur += quoting(cur);
		else if (*cur == ' ')
		{
			spl_num++;
			cur++;
		}
		else
			cur++;
	}
	return (spl_num);
}

static void fill_expan_split(char **expan, char *token)
{
	char *cur;
	int	i;
	long s;

	cur = token;
	s = 0;
	i = 0;
	while (*cur)
	{
		if (*cur == '\'' || *cur == '\"')
			cur += quoting(cur);
		else if (*cur == ' ')
		{
			if (cur != token)
			{
				expan[i] = ft_substr(token, s, cur - token - s);
				if (!expan[i])
					exit(malloc_err);
			}
			while (*cur == ' ')
				cur++;
			s = cur - token;
			i++;
		}
		else
			cur++;
	}
	if (cur - token - s > 0)
		expan[i] = ft_substr(token, s, cur - token - s);
}

char ** variable_expansion(char **token, t_env *env)
{
	int	spl_num;
	char **expan;

	exec_expansion(token, env);
	spl_num = get_size(*token);
	expan = (char **) malloc(sizeof(char *) * (spl_num + 1));
	if (!expan)
		exit (malloc_err);
	expan[spl_num] = NULL;
	fill_expan_split(expan, *token);
	return (expan);
}

//int main(int argc, char *argv[], char *env[])
//{
//	char *str = ft_strdup(" $OLDPWD $SHLVL $abracadabra ");
//	t_env	*env_start;
//
//	get_env_hash(&env_start, env);
//	variable_expansion(&str, env_start);
//	printf("%s\n", str);
//	clean_env_hash(env_start);
//	free(str);
//}