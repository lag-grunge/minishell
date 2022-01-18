#include "ft_dlst.h"
#include "libft.h"

t_dlist	*ft_dlst_new_elem(void *content)
{
	t_dlist *new_elem;

	new_elem = (t_dlist *)malloc(sizeof(t_dlist));
	new_elem->content = content;
	new_elem->next = new_elem;
	new_elem->prev = new_elem;
	return (new_elem);
}

void	ft_dlst_add(t_dlist **dlst, t_dlist *new_elem)
{
	t_dlist *tmp;

	tmp = *dlst;
	*dlst = new_elem;
    if (!tmp)
    {
        (*dlst)->next = *dlst;
        (*dlst)->prev = *dlst;
        return ;
    }
    (*dlst)->next = tmp;
    (*dlst)->prev = tmp->prev;
    tmp->prev->next = *dlst;
    tmp->prev = *dlst;
}

size_t ft_dlst_size(t_dlist *dlst)
{
    size_t  res;
    t_dlist *tmp;

    if (!dlst)
        return (0);
    res = 1;
    tmp = dlst;
    while (dlst->next != tmp)
    {
        dlst = dlst->next;
        res++;
    }
    return (res);
}

t_dlist   *ft_dlst_pop(t_dlist **dlst, t_dlist *cur)
{
    t_dlist *neigh_next;
    t_dlist *neigh_prev;

    if (!dlst || !*dlst || !cur)
        return NULL;
    neigh_next = cur->next;
    neigh_prev = cur->prev;
    if (*dlst == cur)
    {
        *dlst = neigh_next;
        if (neigh_next == cur)
            *dlst = NULL;
    }
    neigh_next->prev = neigh_prev;
    neigh_prev->next = neigh_next;
    cur->next = NULL;
    cur->prev = NULL;
    return (cur);
}

void	ft_dlst_clear(t_dlist **dlst, void	(*free_func)(void *))
{
	t_dlist *tmp;
	t_dlist *next;

	if (!dlst || !*dlst)
		return ;
	tmp = *dlst;
	next = NULL;
	while (tmp != *dlst || next == NULL)
	{
		next = tmp->next;
		free_func(tmp->content);
		tmp->prev = NULL;
		tmp->next = NULL;
		free(tmp);
		tmp = next;
	}
	*dlst = NULL;
}
/*
int main(int argc, char *argv[])
{
	size_t	i;
	t_dlist	*dlst;
	t_dlist	*tmp;
	
	i = 1;
	while (i < argc)
	{
		ft_dlst_add(&dlst, argv[i]);
		i++;
	}
	i = 1;
	tmp = dlst;
	while (i < argc)
	{
		ft_putstr_fd(tmp->content, 1);
		printf("%p\n", tmp);
		i++;
		tmp = tmp->next;
	}
	ft_dlst_clear(dlst, free);
}*/
