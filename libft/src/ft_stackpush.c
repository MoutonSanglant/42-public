#include <libft.h>

void	ft_stackpush(t_stack **astack, t_stack *new)
{
	new->prev = *astack;
	*astack = new;
}
