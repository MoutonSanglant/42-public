#include "fdf.h"

void	draw_3dgrid(t_mlx_sess *p)
{
	static t_vector3	from;
	static t_vector3	to;

	from.x = 12;
	from.y = 12;
	from.z = 12;
	to.x = 30;
	to.y = 30;
	to.z = 30;
	draw_line((t_mlx_sess *)p, from, to);
	//draw_picture((t_mlx_sess *)p);
}
