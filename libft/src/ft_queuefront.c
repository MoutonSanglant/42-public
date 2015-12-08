#include <libft.h>

t_queue		*ft_queuefront(t_queue *queue)
{
	if (queue->prev)
		return (ft_queuefront(queue->prev));
	return (queue);
}
