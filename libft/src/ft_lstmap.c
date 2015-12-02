#include <libft.h>

static void		delelem(void *content, size_t content_size)
{
	if (content_size > 0)
		ft_memdel(&content);
}

t_list			*ft_lstmap(t_list *lst, t_list (*f)(t_list *elem))
{
	t_list	*new_list;

	if (lst->next)
		ft_lstmap(lst->next, f);

	*lst = f(lst);
	new_list = ft_lstnew(lst->content, lst->content_size);
	if (!new_list)
		ft_lstdel(&lst, &delelem);

	return (new_list);
}
