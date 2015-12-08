#include <libft.h>

int		ft_stacksize(t_stack *stack)
{
	t_stack	*top;
	int			i;

	top = stack;
	i = 0;
	while (top->prev)
	{
		top = top->prev;
		i++;
	}
	return (i);
}
