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

# define ABS(x) (x < 0) ? -x : x

# define DEG(x) (x * 180.0 / M_PI)
# define RAD(x) (x * M_PI / 180.0)

//typedef float t_matrix4[4][4];
typedef float t_matrix4[16];

typedef struct	s_vector2
{
	float		x;
	float		y;
}				t_vector2;

typedef struct	s_vector3
{
	float		x;
	float		y;
	float		z;
}				t_vector3;

typedef struct	s_vector4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vector4;

typedef struct	s_triangle
{
	t_vector3	a;
	t_vector3	b;
	t_vector3	c;
}				t_triangle;

typedef struct s_grid
{
	int		width;
	int		height;
	t_triangle	*triangles;
}				t_grid;

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
	t_grid		*grid;
	t_triangle	*cube;
	int			col;
	t_matrix4	*world;
	t_matrix4	*worldToCamera;
	t_matrix4	*view;
	t_matrix4	*projection;
	int			width;
	int			height;
	int			canvasW;
	int			canvasH;
}				t_mlx_sess;

void	draw_line(t_mlx_sess *, t_vector2 *, t_vector2 *);
void	draw_square(t_mlx_sess *, int color, t_vector2 *, t_vector2 *);
//void	draw_line(t_mlx_sess *, t_vector3, t_vector3);
void	draw_picture(t_mlx_sess *);

void	clear_canvas(t_mlx_sess *, int);

void	cube(t_triangle *);
void	init_grid(t_grid *, int, int);
void	draw_3dgrid(t_mlx_sess *);

void	set_image_pixel(t_image * img, int color, int x, int y);

/*
**	MATRIX
*/

void	identity_matrix4(t_matrix4 *);
void	inverse_matrix4(t_matrix4 *, t_matrix4 *);
void	translation_matrix4(t_matrix4 *, t_vector3);
void	scaling_matrix4(t_matrix4 *, t_vector3);
//t_matrix4	*rotate_matrix4(t_matrix4 *, t_matrix4 *);
//t_matrix4	*rotate_matrix4(t_matrix4 *, float);
void	rotationX_matrix4(t_matrix4 *, float);
void	rotationY_matrix4(t_matrix4 *, float);
void	rotationZ_matrix4(t_matrix4 *, float);
void	perspective_projection_matrix4(t_matrix4 *, float, float, int, int);
void	orthographic_projection_matrix4(t_matrix4 *, t_vector2,	int, int);

void	transpose_matrix4(t_matrix4 *m);
void	matrix4_product(t_matrix4 *, t_matrix4 *);
t_vector3	apply_matrix4(t_vector3, t_matrix4 *);

# ifdef DEBUG
void	output_image_info(t_image *image);
# endif
#endif
