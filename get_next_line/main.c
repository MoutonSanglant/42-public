#include <fcntl.h>
#include <libft.h>

#include "get_next_line.h"

int		main(int argc, char **argv)
{
	int		i;
	int		r;
	int		*fd;
	char	*line;

	line = NULL;
	if (argc <= 1)
		return (-1);

	fd = (int *)malloc(sizeof(int) * 3);
	fd[0] = open(argv[1], O_RDONLY);
	fd[1] = open(argv[2], O_RDONLY);
	fd[2] = open(argv[3], O_RDONLY);

	while (fd[0] || fd[1] || fd[2])
	{
		i = 0;
		while (i < 3)
		{
			if (!fd[i])
			{
				i++;
				continue;
			}
			r = get_next_line(fd[i], &line);
			if (r > 0)
			{
				ft_putstr(argv[i + 1]);
				ft_putstr(": ");
				ft_putendl(line);
			}
			else if (r == 0)
				fd[i] = 0;
			else
			{
				ft_putendl("Memory error");
				return (1);
			}
			i++;
		}
	}
	return (0);
}
