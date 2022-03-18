/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filename.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 22:04:27 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/18 23:28:15 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expansions.h"

static int	get_size(char *pwd, char *token)
{
	DIR				*dir;
	struct dirent	*cont;
	int				i;

	dir = opendir(pwd);
	i = 0;
	while (1)
	{
		cont = readdir(dir);
		if (!cont)
			break ;
		if (cont->d_name[0] == '.')
			continue ;
		if (!match(cont->d_name, token))
			continue ;
		i++;
	}
	closedir(dir);
	return (i);
}

static t_list	*oper_filename(char *filename, t_list *args_list)
{
	char			*tmp;

	tmp = ft_strdup(filename);
	if (!tmp)
		exit(malloc_err);
	write_word(&args_list, tmp);
	return (args_list->next);
}

static void	write_filenames(t_list *args_list, DIR *dir, \
		int fil_num, char *pattern)
{
	struct dirent	*cont;
	int				i;
	char			*tmp;

	i = 0;
	while (i < fil_num)
	{
		cont = readdir(dir);
		if (!cont)
			break ;
		if (cont->d_name[0] == '.')
			continue ;
		if (match(cont->d_name, pattern))
		{
			args_list = oper_filename(cont->d_name, args_list);
			i++;
		}
	}
	if (i)
		return ;
	tmp = quote_removal(args_list->content);
	write_word(&args_list, tmp);
}

void	filename_expansion(t_list *args_list)
{
	DIR		*dir;
	int		fil_num;
	char	pwd[2048];
	char	*pattern;

	getcwd(pwd, 2048);
	if (access(pwd, F_OK))
		return ;
	pattern = ft_strdup(args_list->content);
	fil_num = get_size(pwd, pattern);
	dir = opendir(pwd);
	args_list = ft_lstins_few_empty(args_list, fil_num - 1);
	write_filenames(args_list, dir, fil_num, pattern);
	closedir(dir);
	free(pattern);
}
