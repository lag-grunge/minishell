#include "../../includes/minishell.h"
#include "../../includes/syntax.h"
#include "../../includes/environment.h"
#include "../../includes/clean.h"

static char *ft_name(char *start)
{
	if (!ft_isalpha(*start) && *start != '_')
		return (start);
	while (ft_isalnum(*start) || *start == '_')
		start++;
	return (start);
}

char *make_substitution(char **tokens, char *dollar, char *end_var, char *value)
{
	int	count;
	char *new_str;
	int val;
	char *ret;

	val = (int)ft_strlen(value);
	count = (int)ft_strlen(*tokens);
	count -= (int)(end_var - dollar);
	count += val;
	new_str = (char *) malloc(sizeof(char) * (count + 1));
	if (!new_str)
		exit (malloc_err);
	ft_strlcpy(new_str, *tokens, dollar - *tokens + 1);
	ft_strlcat(new_str, value, dollar - *tokens + val + 1);
	ret = new_str + ft_strlen(new_str);
	ft_strlcat(new_str, end_var, count + 1);
	free(*tokens);
	*tokens = new_str;
	return (ret);
}

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
	value = get_key_value(env, tmp);
	free(tmp);
	ret = make_substitution(tokens, dollar, end_var, value);
	free(value);
	return (ret);
}

void	variable_expansion(char **tokens, t_env *env)
{
	char *cur;

	cur = *tokens;
	while (*cur)
	{
		if (*cur == '$')
			cur = oper_dollar(tokens, cur, env);
		else if (*cur == '\'')
			cur += quoting(cur);
		else
			cur++;
	}
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