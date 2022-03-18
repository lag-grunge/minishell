/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fphlox <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 02:57:03 by fphlox            #+#    #+#             */
/*   Updated: 2022/03/15 02:57:04 by fphlox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "biltins.h"

static void	ft_export_els(t_list *orgs, t_env *local_env, char *vs, int j)
{
	char	*name;
	char	*value;
	int		i;

	name = ft_substr(orgs->content, 0, j);
	if (name == NULL)
		exit (malloc_err);
	i = ft_strlen(orgs->content);
	if (vs[j] != '\0')
	{
		value = ft_substr(orgs->content, j + 1, i);
		if (value == NULL)
			exit (malloc_err);
	}
	else
		value = NULL;
	set_value(&local_env, name, value);
	free (name);
}

static void	ft_export_pls(t_list *orgs, t_env *local_env, char *vs, int j)
{
	t_exp	e;

	e.name = ft_substr(orgs->content, 0, j);
	if (e.name == NULL)
		exit (malloc_err);
	j++;
	if (vs[j] != '\0')
		e.value = ft_substr(orgs->content, j + 1, ft_strlen(orgs->content));
	else
		e.value = NULL;
	e.old = get_value(local_env, e.name);
	if (e.old != NULL)
	{
		e.full = ft_strjoin(e.old, e.value);
		if (e.full == NULL)
			exit (malloc_err);
		free (e.old);
		free (e.value);
		set_value(&local_env, e.name, e.full);
	}
	else
		set_value(&local_env, e.name, e.value);
	free (e.name);
}

static int	ft_export_args(t_list *orgs, t_env *local_env, int *ret, int j)
{
	char	*vs;

	vs = (char *) orgs->content;
	if ((vs[0] < 'A') || (vs[0] > 'z') || ((vs[0] > 'Z') && (vs[0] < 'a')))
	{
		er_mes ("minishell: export: `", vs, "': not a valid identifier\n");
		ret[0] = 1;
		return (1);
	}
	while ((vs[j] != '=') && (vs[j] != '+') && (vs[j] != '\0'))
		j++;
	if (vs[j] == '+')
	{
		if (vs[j + 1] != '=')
		{
			er_mes("minishell: export: `", vs, "': not a valid identifier\n");
			ret[0] = 1;
			return (1);
		}
		ft_export_pls(orgs, local_env, vs, j);
	}
	else
		ft_export_els(orgs, local_env, vs, j);
	return (0);
}

static	void	ft_printf_export(t_env *local_env)
{
	write (1, "declare -x ", 11);
	ft_putstr_fd(local_env->key, 1);
	if (local_env->value != NULL)
	{
		write (1, "=\"", 2);
		ft_putstr_fd(local_env->value, 1);
		write (1, "\"", 1);
	}
	write (1, "\n", 1);
}

int	ft_export(t_list *orgs, t_env *local_env)
{
	int	ret;

	ret = 0;
	orgs = orgs->next;
	if (orgs == NULL)
	{
		while (local_env != NULL)
		{
			ft_printf_export(local_env);
			local_env = local_env->next;
		}
	}
	else
	{
		while (orgs != NULL)
		{
			ft_export_args(orgs, local_env, &ret, 0);
			if (ret == 1)
				return (1);
			orgs = orgs->next;
		}
	}
	return (ret);
}
