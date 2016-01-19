#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <includes/libft.h>

/*
** BONUS
*/
# ifdef BONUS
#  include <sys/time.h>
/*
** FPS in microseconds
** 16666 for 60 fps
** 33332 for 30 fps
*/
#  define FPS 33332
# endif

# ifdef LINUX
#  include "../includes/linux/mlx.h"
# else
#  include "../includes/mlx.h"
# endif

typedef double t_matrix4[4][4];

typedef struct	s_vector2
{
	double		x;
	double		y;
}				t_vector2;

typedef struct	s_vector3
{
	double		x;
	double		y;
	double		z;
}				t_vector3;

typedef struct	s_vector4
{
	double		x;
	double		y;
	double		z;
	double		w;
}				t_vector4;

typedef struct	s_image
{
	void	*img;
	char	*data;
	int		sl;
	int		bpp;
	int		endian;
}				t_image;

typedef struct	s_mlx_sess
{
	void		*sess;
	void		*win;
	t_image		*img;
	t_vector3	*grid;
	int			col;
	t_matrix4	*world;
	t_matrix4	*view;
	t_matrix4	*projection;
	int			width;
	int			height;
}				t_mlx_sess;

void	draw_line(t_mlx_sess *, t_vector2 *, t_vector2 *);
void	draw_square(t_mlx_sess *, int color, t_vector2 *, t_vector2 *);
//void	draw_line(t_mlx_sess *, t_vector3, t_vector3);
void	draw_picture(t_mlx_sess *);

void	clear_canvas(t_mlx_sess *, int);

void	init_grid(t_vector3 *grid);
void	draw_3dgrid(t_mlx_sess *);

void	set_image_pixel(t_image * img, int color, int x, int y);

/*
**	MATRIX
*/

t_matrix4	*identity_matrix4(t_matrix4 *);
t_matrix4	*inverse_matrix4(t_matrix4 *);
t_matrix4	*translate_matrix4(t_matrix4 *, t_vector3);
t_matrix4	*scale_matrix4(t_matrix4 *, t_vector3);
//t_matrix4	*rotate_matrix4(t_matrix4 *, t_matrix4 *);
t_matrix4	*rotate_matrix4(t_matrix4 *, double);
t_matrix4	*projection_matrix4(t_matrix4 *, t_matrix4 *);

t_vector4	apply_matrix4(t_vector4, t_matrix4 *);
//t_vector3	apply_matrix4(t_vector3, t_matrix4 *);

# ifdef DEBUG
void	output_image_info(t_image *image);
# endif
#endif
