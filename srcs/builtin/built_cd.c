/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_cd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fphlox <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 03:00:44 by fphlox            #+#    #+#             */
/*   Updated: 2022/03/15 03:00:45 by fphlox           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "biltins.h"

static void	ft_cd_error_message(t_list *orgs)
{
	char	*vs;

	if (errno == 20)
	{
		write (2, "minishell: cd: ", 15);
		vs = (char *) orgs->content;
		ft_putstr_fd(vs, 2);
		write (2, ": Not a directory\n", 18);
	}
	else
	{
		write (2, "minishell: cd: ", 15);
		vs = (char *) orgs->content;
		ft_putstr_fd(vs, 2);
		write (2, ": No such file or directory\n", 28);
	}
}

static int	ft_cd_error(t_list *orgs, t_env *local_env, char *str, int	*ret)
{
	char	*vs;
	char	pwd[4000];

	if (!(getcwd(pwd, 4000)) && (ft_strncmp(orgs->content, ".\0", 2) == 0))
	{
		write (2, "cd: error retrieving current directory: getcwd: cannot", 54);
		write (2, " access parent directories: No such file or directory\n", 54);
		str = get_value (local_env, "PWD");
		set_value(&local_env, "OLDPWD", str);
		vs = ft_strjoin(str, "/.");
		if (vs == NULL)
			exit (malloc_err);
		set_value(&local_env, "PWD", vs);
		return (0);
	}
	ret[0] = chdir(orgs->content);
	if (ret[0] != 0)
	{
		ft_cd_error_message(orgs);
		return (1);
	}
	return (2);
}

static int	ft_cd_home(t_env *local_env)
{
	char	*str;
	int		ret;
	char	pwd[4000];

	str = get_value(local_env, "HOME");
	if (str == NULL)
	{
		write (2, "minishell: cd: HOME not set\n", 28);
		return (1);
	}
	ret = chdir(str);
	free (str);
	str = get_value (local_env, "PWD");
	set_value(&local_env, "OLDPWD", str);
	getcwd(pwd, 4000);
	str = ft_strdup(pwd);
	if (str == NULL)
		exit (malloc_err);
	set_value(&local_env, "PWD", str);
	return (ret);
}

int	ft_cd(t_list *orgs, t_env *local_env)
{
	int		ret;
	int		er;
	char	*str;
	char	pwd[4000];

	orgs = orgs->next;
	if (orgs != NULL)
	{
		er = ft_cd_error(orgs, local_env, NULL, &ret);
		if (er != 2)
			return (er);
		str = get_value (local_env, "PWD");
		set_value(&local_env, "OLDPWD", str);
		getcwd(pwd, 4000);
		str = ft_strdup(pwd);
		if (str == NULL)
			exit (malloc_err);
		set_value(&local_env, "PWD", str);
	}
	else
		ret = ft_cd_home(local_env);
	return (ret);
}
