/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   biltins.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fphlox <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 18:49:50 by fphlox            #+#    #+#             */
/*   Updated: 2022/03/16 21:08:03 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "biltins.h"

void	er_mes(char *start, char *content, char *end)
{
	if (start != NULL)
		ft_putstr_fd(start, 2);
	if (content != NULL)
		ft_putstr_fd(content, 2);
	if (end != NULL)
		ft_putstr_fd(end, 2);
}

int	ft_env(t_list *orgs, t_env *local_env)
{
	orgs = orgs->next;
	if (orgs == NULL)
	{
		while (local_env != NULL)
		{
			if (local_env->value != NULL)
			{
				ft_putstr_fd(local_env->key, 1);
				if (local_env->value != NULL)
					write (1, "=", 1);
				if (local_env->value != NULL)
					ft_putstr_fd(local_env->value, 1);
				write (1, "\n", 1);
			}
			local_env = local_env->next;
		}
	}
	else
		er_mes("env: ", (char *)orgs->content, ": No such file or directory\n");
	return (0);
}

int	ft_unset(t_list *orgs, t_env *local_env)
{
	orgs = orgs->next;
	while (orgs != NULL)
	{
		unset_value(&local_env, orgs->content);
		orgs = orgs->next;
	}
	return (0);
}

int	ft_pwd(t_list *orgs, t_env *local_env)
{
	char	pwd[4000];
	char	*str;

	orgs = orgs->next;
	if (getcwd(pwd, 4000) == NULL)
	{
		str = get_value (local_env, "PWD");
		ft_putstr_fd(str, 1);
		write (1, "\n", 1);
		return (0);
	}
	ft_putstr_fd(pwd, 1);
	write (1, "\n", 1);
	return (0);
}

int	ft_echo(t_list *orgs)
{
	int		n;
	char	*vs;

	n = 0;
	orgs = orgs->next;
	if (orgs != NULL)
	{
		while ((orgs != NULL) && (ft_strncmp(orgs->content, "-n\0", 3) == 0))
		{
			n = 1;
			orgs = orgs->next;
		}
		while (orgs != NULL)
		{
			vs = (char *) orgs->content;
			ft_putstr_fd(vs, 1);
			orgs = orgs->next;
			if (orgs != NULL)
				write (1, " ", 1);
		}
	}
	if (n == 0)
		write (1, "\n", 1);
	return (0);
}
