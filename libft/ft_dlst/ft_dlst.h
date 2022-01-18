#ifndef FT_DLIST_H
# define FT_DLIST_H

#include <stddef.h>

typedef struct s_dlist	{
	void			*content;
	struct s_dlist	*next;
	struct s_dlist	*prev;
}	t_dlist;

t_dlist	*ft_dlst_new_elem(void *content);
void	ft_dlst_add(t_dlist **dlst, t_dlist *new_elem);
size_t  ft_dlst_size(t_dlist *dlst);
t_dlist *ft_dlst_pop(t_dlist **dlst, t_dlist *cur);
void	ft_dlst_clear(t_dlist **dlst, void (*free_func)(void *));

void    ft_dlstmap(t_dlist *dlst, void (*proc)(t_dlist *, void *), void *params);


#endif
