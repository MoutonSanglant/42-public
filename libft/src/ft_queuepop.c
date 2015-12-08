#include <libft.h>

void	ft_queuepopfront(t_queue **aqueue)
{
	t_queue	*first;

	first = ft_queuefront(*aqueue);
	if (first->next)
	{
		*aqueue = first->next;
		(*aqueue)->prev = NULL;
		ft_memdel((void *)&first);
	}
	else
		ft_memdel((void **)aqueue);
}
