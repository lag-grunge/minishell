#include "minishell.h"
#include "environment.h"

int get_env_hash(t_env **env_start, char **env)
{
	t_env	*cur;

	if (!*env)
	{
		*env_start = NULL;
		return (-1);
	}
	cur = ft_env_new_elem();
	if (!cur)
		exit (malloc_err);
	write_key_value_to_elem(cur, "last_status=0", 0);
	*env_start = cur;
	while (*env)
	{
		cur->next = ft_env_new_elem();
		cur = cur->next;
		if (!cur)
			exit (malloc_err);
		write_key_value_to_elem(cur, *env, 1);
		env++;
	}
	return (0);
}

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
	if (!size)
		return (NULL);
	env_array = (char **) malloc(sizeof(char *) * (size + 1));
	if (!env_array)
		exit(malloc_err);
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

void	print_env(t_env *env_hash)
{
	while (env_hash)
	{
		printf("declare -x ");
		printf("%s", env_hash->key);
		if (env_hash->sep == '=')
			printf("=");
		if (env_hash->value)
			printf("\"%s\"", env_hash->value);
		printf("\n");
		env_hash = env_hash->next;
	}
}