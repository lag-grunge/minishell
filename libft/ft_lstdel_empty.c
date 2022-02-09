/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_empty.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdalton <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 23:23:53 by sdalton           #+#    #+#             */
/*   Updated: 2022/02/03 23:24:07 by sdalton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdel_empty(t_list **list)
{
	t_list	*cur;
	t_list	*prev;
	t_list	*tmp;

	cur = *list;
	prev = NULL;
	while (cur)
	{
		if (NULL == cur->content || *(char *)cur->content == '\0')
		{
			tmp = cur;
			if (!prev)
				*list = cur->next;
			else
				prev->next = cur->next;
			cur = cur->next;
			ft_lstdelone(tmp, free);
		}
		else
		{
			prev = cur;
			cur = cur->next;
		}
	}
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
	printf("-----\n");
	ft_lstins_few_empty(list, 4);
	 i = 0;
	cur = list->next;
	while (i < 4)
	{
		cur->content = ft_itoa(i + 10);
		cur = cur->next;
		i++;
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
	ft_lstins_few_empty(list, 3);
	cur = list;
	while (cur)
	{
		printf("%p\n", cur->content);
		cur = cur->next;
	}
	printf("-----\n");
	ft_lstdel_empty(&list);
	cur = list;
	while (cur)
	{
		printf("%s\n", cur->content);
		cur = cur->next;
	}
}
*/
