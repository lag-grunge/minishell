#include "../includes/minishell.h"
#include "environment.h"

static	int get_size(t_env *env_hash)
{
	int	i;

	if (!env_hash)
		return (0);
	i = 1;
	while (env_hash->next)
	{
		env_hash = env_hash->next;
		i++;
	}
	return (i);
}

static char *cat_env_str(t_env *env_hash)
{
	char	*new_str;
	int		len;
	int		keylen;

	keylen = (int)ft_strlen(env_hash->key);
	len = keylen;
	if (env_hash->sep)
		len += 1;
	if (env_hash->value)
		len += (int)ft_strlen(env_hash->value);
	new_str = (char *) malloc(sizeof(char) * (len + 1));
	if (!new_str)
		exit (malloc_err);
	ft_strlcpy(new_str, env_hash->key, keylen + 1);
	if (env_hash->sep)
	{
		new_str[keylen] = '=';
		new_str[keylen + 1] = 0;
	}
	if (env_hash->value)
		ft_strlcat(new_str, env_hash->value, len + 1);
	return (new_str);
}

char	**get_env_array(t_env *env_hash)
{
	int		size;
	char	**env_array;
	int		i;

	size = get_size(env_hash);
	env_array = (char **) malloc(sizeof(char *) * (size + 1));
	env_array[size] = NULL;
	i = 0;
	while (i < size)
	{
		env_array[i] = cat_env_str(env_hash);
		i++;
		env_hash = env_hash->next;
	}
	return (env_array);
}

int set_key_value(t_env *env, char *key, char *value)
{
	while (env)
	{
		if (!ft_strncmp(env->key, key, ft_strlen(key)))
		{
			if (env->value)
				free(env->value);
			env->sep = '=';
			env->value = value;
		}
		env = env->next;
	}
}

int	increment_shell_level(void)
{
	char	*s1;
	char	*s2;

	s1 = get_key_value(g_data.env, "SHLVL");
	if (!s1)
		exit (malloc_err);
	s2 = ft_itoa(ft_atoi(s1) + 1);
	free(s1);
	if (!s2)
		exit (malloc_err);
	set_key_value(g_data.env, "", 0);
	free(s2);
	return (0);
}

//int main(int argc, char *argv[], char *env[])
//{
//	char **env2;
//
//	get_env_hash(&g_data.env, env);
//	write_key_value(&g_data.env, "b=", 0);
//	write_key_value(&g_data.env, "a", 0);
//	env2 = get_env_array(g_data.env);
//	while (*env2)
//	{
//		printf("%s\n", *env2);
//		env2++;
//	}
//	return (0);
//}