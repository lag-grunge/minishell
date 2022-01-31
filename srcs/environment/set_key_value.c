#include "minishell.h"
#include "environment.h"

int set_key_value(t_env **env, char *key, char *value, int new)
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
	if (new)
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
