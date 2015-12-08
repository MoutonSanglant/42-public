#include <libft.h>

void	ft_queuepush(t_queue *queue, t_queue *new)
{
	t_queue	*last;

	last = ft_queueback(queue);
	last->next = new;
	new->prev = last;
}
