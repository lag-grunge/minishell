#include "minishell.h"
#include "clean.h"

char *get_key_value(t_env *env, char *key)
{
	int len_key;

	len_key = (int)ft_strlen(key);
	while (env)
	{
		if (len_key == ft_strlen(env->key) &&\
			!ft_strncmp(env->key, key, len_key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}

static t_env *ft_env_new_elem(void)
{
	t_env	*new_elem;

	new_elem = (t_env *) malloc(sizeof(t_env));
	if (!new_elem)
		return (NULL);
	new_elem->key = NULL;
	new_elem->sep = 0;
	new_elem->value = NULL;
	new_elem->next = NULL;
	return (new_elem);
}

static int write_key_value_to_elem(t_env *cur, char *cur_env, int start)
{
	char *tmp;
	char *sep;

	sep = ft_strchr(cur_env, '=');
	if (sep)
		tmp = ft_substr(cur_env, 0, sep - cur_env);
	else
		tmp = ft_strdup(cur_env);
	if (!tmp)
		exit (malloc_err);
	cur->key = ft_strdup(tmp);
	if (sep)
		cur->sep = '=';
	if (sep && start)
		cur->value = ft_strdup(getenv(tmp));
	else if (sep)
		cur->value = ft_substr(sep, 1, ft_strlen(sep));
	free(tmp);
	if ((sep &&!cur->key) || (sep && !cur->value))
		exit (malloc_err);
	return (0);
}


int write_key_value(t_env **env_hash, char *cur_env, int start)
{
	t_env *cur_hash;

	if (!*env_hash)
	{
		*env_hash = ft_env_new_elem();
		cur_hash = *env_hash;
	}
	else
	{
		cur_hash = *env_hash;
		while (cur_hash->next)
			cur_hash = cur_hash->next;
		cur_hash->next = ft_env_new_elem();
		cur_hash = cur_hash->next;
	}
	write_key_value_to_elem(cur_hash, cur_env, start);
	return (0);
}

int get_env_hash(t_env **env_start, char **env)
{
	t_env	*cur;

	if (!*env)
	{
		*env_start = NULL;
		return (0);
	}
	while (*env)
	{
		write_key_value(env_start, *env, 1);
		env++;
	}
	return (0);
}

//
//int main(int argc, char *argv[], char *env[])
//{
//	t_env	*env_hash;
//	t_env	*cur;
//	int		ret;
//
//	env_hash = NULL;
//	ret = get_env_hash(&env_hash, env);
//	if (ret)
//		return (ret);
//	cur = env_hash;
//	while (cur)
//	{
//		printf("%s=%s\n", cur->key, cur->value);
//		cur = cur->next;
//	}
//	clean_env_hash(env_hash);
//	return (0);
//}