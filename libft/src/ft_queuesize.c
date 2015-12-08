#include <libft.h>

int		ft_queuesize(t_queue *queue)
{
	t_queue	*first;
	int			i;

	first = ft_queuefront(queue);
	i = 0;
	while (first->next)
	{
		first = first->next;
		i++;
	}
	return (i);
}
