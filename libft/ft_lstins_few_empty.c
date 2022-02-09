/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstins_few_empty.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/02 23:08:47 by sdalton           #+#    #+#             */
/*   Updated: 2022/02/02 23:10:18 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstins_few_empty(t_list *list, int num)
{
	t_list	*new;
	t_list	*next;
	t_list	*cur;

	if (!list)
	{
		new = ft_lstnew(NULL);
		if (!new)
			return (NULL);
		list = new;
		num--;
	}
	cur = list;
	next = list->next;
	while (num > 0)
	{
		cur->next = ft_lstnew(NULL);
		if (!cur->next)
			return (NULL);
		cur = cur->next;
		num--;
	}
	cur->next = next;
	return (list);
}
/*
#include <stdio.h>

int main(int argc, char *argv[])
{
	t_list *cur;
	t_list *list;

	cur = NULL;
	list = ft_lstins_few_empty(cur, argc);
	cur = list;
	while (argc)
	{
		cur->content = ft_strdup(*argv++);
		cur = cur->next;
		argc--;
	}
	ft_lstins_few_empty(list, 3);
	int i = 0;
	cur = list->next;
	while (i < 3)
	{
		cur->content = ft_itoa(i);
		cur = cur->next;
		i++;
	}
	cur = list;
	while (cur)
	{
		printf("%s\n", (char *)cur->content);
		cur = cur->next;
	}
	t_list *cur_last = ft_lstlast(list);
	ft_lstins_few_empty(cur_last, 3);
	i = 0;
	cur = cur_last->next;
	while (i < 3)
	{
		cur->content = ft_itoa(i);
		cur = cur->next;
		i++;
	}
	cur = list;
	while (cur)
	{
		printf("%s\n", (char *)cur->content);
		cur = cur->next;
	}
}*/
