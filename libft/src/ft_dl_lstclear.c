#include <libft.h>

void	ft_dl_lstclear(t_dl_list **alst)
{
	if ((*alst)->next)
		ft_dl_lstclear(&(*alst)->next);
	ft_memdel((void **)alst);
}
