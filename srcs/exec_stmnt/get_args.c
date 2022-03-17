/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_args.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 01:19:24 by sdalton           #+#    #+#             */
/*   Updated: 2022/03/18 01:19:35 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_size(t_list *cmd_args)
{
	int	i;

	if (!cmd_args)
		return (0);
	i = 1;
	while (cmd_args->next)
	{
		cmd_args = cmd_args->next;
		i++;
	}
	return (i);
}

char	**get_cmd_array(t_list *args_list)
{
	int		size;
	char	**cmd_array;
	int		i;

	size = get_size(args_list);
	if (!size)
		return (NULL);
	cmd_array = (char **) malloc(sizeof(char *) * (size + 1));
	if (!cmd_array)
		exit(malloc_err);
	cmd_array[size] = NULL;
	i = 0;
	while (i < size)
	{
		cmd_array[i] = ft_strdup(args_list->content);
		if (!cmd_array[i])
			exit(malloc_err);
		i++;
		args_list = args_list->next;
	}
	return (cmd_array);
}
