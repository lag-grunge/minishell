/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_which.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 00:13:29 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/18 00:13:40 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "exec_stmnt.h"
#include "environment.h"

static char	*get_fp(char *dir, char *cmd)
{
	char	*fp;
	size_t	fp_len;
	size_t	dir_len;

	dir_len = ft_strlen(dir);
	fp_len = dir_len + ft_strlen(cmd) + 1;
	fp = malloc(sizeof(char) * (fp_len + 1));
	ft_strlcpy(fp, dir, dir_len + 1);
	fp[dir_len] = '/';
	fp[dir_len + 1] = 0;
	ft_strlcat(fp, cmd, fp_len + 1);
	return (fp);
}

static int	find_cmd_in_var(char **exec_path, char *cmd, char *var)
{
	size_t	i;
	char	**s;
	char	*fp;

	i = 0;
	s = ft_split(var, ':');
	*exec_path = NULL;
	while (s[i])
	{
		fp = get_fp(s[i], cmd);
		if (!access(fp, F_OK))
		{
			clean_split(s, ft_spllen(s));
			if (!access(fp, X_OK))
			{
				*exec_path = fp;
				return (0);
			}
			return (not_perms_for_exec);
		}
		free(fp);
		i++;
	}
	clean_split(s, ft_spllen(s));
	return (not_fnd_bin_in_path);
}

int	ft_which(char **exec_path, char *cmd)
{
	char	*path_str;
	int		find_cmd;

	if (cmd[0] == 0)
		return (1);
	else if (ft_strchr(cmd, '/'))
	{
		*exec_path = cmd;
		return (0);
	}
	path_str = get_value(g_data.env, "PATH");
	if (path_str == NULL)
		return (nopath_in_env);
	find_cmd = find_cmd_in_var(exec_path, cmd, path_str);
	free(path_str);
	if (!find_cmd)
		return (0);
	return (find_cmd);
}
