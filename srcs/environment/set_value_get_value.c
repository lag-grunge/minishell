#include "minishell.h"
#include "environment.h"

/* set value to the key, free old one
 * if key not exist and new is True create new elem */

int set_value(t_env **env, char *key, char *value, int new_val)
{
	t_env	*tmp;
	t_env	*cur;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key)))
		{
			if (tmp->value)
				free(tmp->value);
			tmp->sep = '=';
			tmp->value = value;
			return (0);
		}
		cur = tmp;
		tmp = tmp->next;
	}
	if (new_val)
	{
		tmp = ft_env_new_elem();
		tmp->key = ft_strdup(key);
		tmp->sep = '=';
		tmp->value = ft_strdup(value);
		if (!tmp->key || !tmp->value)
			exit (malloc_err);
		if (!*env)
			*env = tmp;
		else
			cur->next = tmp;
		return (0);
	}
	return (1);
}

/*
 * get_value returns value (char *) corresponds key or empty if key not in env
 * get_value allocates memory
 */
char *get_value(t_env *env, char *key)
{
	int len_key;

	len_key = (int)ft_strlen(key);
	while (env)
	{
		if (len_key == (int)ft_strlen(env->key) &&\
			!ft_strncmp(env->key, key, len_key))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (ft_strdup(""));
}
