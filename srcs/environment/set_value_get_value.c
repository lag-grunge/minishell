#include "minishell.h"
#include "environment.h"
#include "clean.h"

static void add_new_value(t_env **last, char *key, char *value)
{
	t_env *tmp;

	tmp = ft_env_new_elem();
	tmp->key = ft_strdup(key);
	if (value)
	{
		tmp->sep = '=';
		tmp->value = value;
		if (!tmp->value)
			exit (malloc_err);
	}
	if (!tmp->key)
		exit (malloc_err);
	*last = tmp;
}

/* set value to the key, free old one
 * if key not exist create new elem */
/* not protected from NULL */
/* key not free */


int set_value(t_env **env, char *key, char *value)
{
	t_env	*tmp;
	t_env	**last;

	tmp = *env;
	last = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, key, ft_strlen(key) + 1))
		{
			if (tmp->value && value)
				free(tmp->value);
			if (value)
				tmp->sep = '=';
			if (value)
				tmp->value = value;
			return (0);
		}
		last = &tmp->next;
		tmp = tmp->next;
	}
	add_new_value(last, key, value);
	return (1);
}

int unset_value(t_env **env, char *key)
{
    t_env   **prev;
    t_env	*cur;

    prev = env;
    cur = *env;
    while (cur)
    {
        if (!ft_strncmp(cur->key, key, ft_strlen(key) + 1))
        {
            *prev = cur->next;
            g_data.env = *env;
            del_env_one(cur);
            return (1);
        }
        prev = &cur->next;
        cur = cur->next;
    }
    return (0);
}

/*
 * get_value returns value (char *) corresponds key or empty if key not in env
 * get_value allocates memory
 */
char *get_value(t_env *env, char *key)
{
	int     len_key;
    char    *tmp;

	len_key = (int)ft_strlen(key);
	while (env)
	{
		if (len_key == (int)ft_strlen(env->key) &&\
			!ft_strncmp(env->key, key, len_key + 1))
		{
			if (env->value != NULL)
			{
				tmp = ft_strdup(env->value);
				if (!tmp)
					exit(malloc_err);
				return (tmp);
			}
			else
				return (NULL);
        }
		env = env->next;
	}
	return (NULL);
}
