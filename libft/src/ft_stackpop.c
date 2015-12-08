#include <libft.h>

void	ft_stackpop(t_stack **astack)
{
	t_stack	*top;

	top = *astack;
	if (top->prev)
	{
		*astack = top->prev;
		ft_memdel((void *)&top);
	}
	else
		ft_memdel((void **) astack);
}
