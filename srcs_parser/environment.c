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

static int write_key_value(t_env *cur, char *cur_env)
{
	char *tmp;
	char *sep;

	sep = ft_strchr(cur_env, '=');
	if (sep)
		tmp = ft_substr(cur_env, 0, sep - cur_env);
	else
		tmp = ft_strdup(cur_env);
	if (!tmp)
		return (malloc_err);
	cur->key = ft_strdup(tmp);
	cur->sep = '=';
	if (sep)
		cur->value = ft_strdup(getenv(tmp));
	else
		cur->value = ft_strdup("");
	free(tmp);
	if (!cur->key || !cur->value)
		return (malloc_err);
	return (0);
}

int get_env_hash(t_env **env_start, char *env[])
{
	t_env	*cur;
	int		ret;

	if (!*env)
	{
		*env_start = NULL;
		return (0);
	}
	*env_start = ft_env_new_elem();
	cur = *env_start;
	ret = 0;
	if (!cur)
		ret = malloc_err;
	while (!ret)
	{
		ret = write_key_value(cur, *env);
		if (ret)
			break ;
		env++;
		if (!*env)
			return (0);
		cur->next = ft_env_new_elem();
		if (!cur->next)
			ret = malloc_err;
		cur = cur->next;
	}
	clean_env_hash(*env_start);
	return (ret);
}


/*int main(int argc, char *argv[], char *env[])
{
	t_env	*env_hash;
	t_env	*cur;
	int		ret;

	env_hash = NULL;
	ret = get_env_hash(&env_hash, env);
	if (ret)
		return (ret);
	cur = env_hash;
	while (cur)
	{
		printf("%s=%s\n", cur->key, cur->value);
		cur = cur->next;
	}
	clean_env_hash(env_hash);
	return (0);
}*/