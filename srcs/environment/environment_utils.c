#include "../includes/minishell.h"
#include "environment.h"

t_env *ft_env_new_elem(void)
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

int write_key_value_to_elem(t_env *cur, char *cur_env, int start)
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

int	increment_shell_level(void)
{
	char	*s1;
	char	*s2;
	int 	num = 0;

	s1 = get_value_set_if_null("SHLVL", "1");
    num = ft_atoi(s1);
	s2 = ft_itoa(num + 1);
	free(s1);
	if (!s2)
		exit (malloc_err);
	set_value(&g_data.env, "SHLVL", s2);
	return (0);
}

char *get_value_set_if_null(char *key, char *value)
{
    char    *tmp;

    tmp = get_value(g_data.env, key);
    if (!tmp)
    {
        tmp = ft_strdup(value);
        if (!tmp)
            exit(malloc_err);
        set_value(&g_data.env, key, tmp);
    }
    return (tmp);
}

int get_last_status(void)
{
 //   char    *tmp;
    int     ret;

 //   tmp = get_value_set_if_null("last_status", "0");
 //   ret = ft_atoi(tmp);
 //   free(tmp);
	ret = g_data.last_stat;
    return (ret);
}
