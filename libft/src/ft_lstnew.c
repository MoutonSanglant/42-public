#include <libft.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *list;

	list = (t_list *)ft_memalloc(sizeof(t_list));
	if (list)
	{
		if (content)
		{
			list->content = ft_memalloc(content_size);
			list->content = ft_memcpy(list->content, content, content_size); 
			list->content_size = content_size;
		}
		else
		{
			list->content = NULL; 
			list->content_size = 0;
		}
		list->next = NULL;
	}
	return (list);
}
