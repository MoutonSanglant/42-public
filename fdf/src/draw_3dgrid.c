#include "fdf.h"

void	draw_3dgrid(t_mlx_sess *p)
{
//	static t_vector3	from;
//	static t_vector3	to;
	static t_vector2	from;
	static t_vector2	to;

	from.x = 100;
	from.y = 100;
//	from.z = 12;
	to.x = 200;
	to.y = 100;
//	to.z = 30;
	p->col = 0xffff0000;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 100;
	to.y = 200;
	p->col = 0xffffff00;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 0;
	to.y = 100;
	p->col = 0x00ffffff;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 100;
	to.y = 0;
	p->col = 0x0000ff00;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 200;
	to.y = 200;
	p->col = 0x0000ffff;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 0;
	to.y = 0;
	p->col = 0x000000ff;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 200;
	to.y = 0;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 0;
	to.y = 200;
	p->col = 0x00ff00ff;
	draw_line((t_mlx_sess *)p, &from, &to);


	to.x = 200;
	to.y = 150;
	p->col = 0x006666ff;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 150;
	to.y = 200;
	p->col = 0x00ff66ff;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 50;
	to.y = 200;
	p->col = 0x0066ffff;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 0;
	to.y = 150;
	p->col = 0x00666600;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 0;
	to.y = 50;
	p->col = 0x00660066;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 50;
	to.y = 0;
	p->col = 0x0066ff00;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 150;
	to.y = 0;
	p->col = 0x0066ff66;
	draw_line((t_mlx_sess *)p, &from, &to);
	to.x = 200;
	to.y = 50;
	p->col = 0x00ff6666;
	draw_line((t_mlx_sess *)p, &from, &to);
	//draw_picture((t_mlx_sess *)p);
	to.x = 180;
	to.y = 180;
	p->col = 0x99ff6666;
//	draw_square((t_mlx_sess *)p, &from, &to);
}
