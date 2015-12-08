#include <libft.h>

t_queue		*ft_queueback(t_queue *queue)
{
	if (queue->next)
		return (ft_queueback(queue->next));
	return (queue);
}
