/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 01:00:57 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 01:00:57 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include <includes/libft.h>

# define BUFF_SIZE 32

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
#  include "../includes/linux/mlx_int.h"

#  define KEY_NUMPAD_MORE	65451
#  define KEY_NUMPAD_LESS	65453
#  define KEY_Q		97
#  define KEY_W		122
#  define KEY_E		101
#  define KEY_A		113
#  define KEY_S		115
#  define KEY_D		100
#  define KEY_LEFT	65361
#  define KEY_RIGHT	65363
#  define KEY_UP	65362
#  define KEY_DOWN	65364

# else
#  include "../includes/mlx.h"
#  define KeyPressMask	(1L<<0)
#  define KeyPress	2

/*
** the '+' key is under the '-' key on mac keyboard
*/
#  define KEY_NUMPAD_MORE	69
#  define KEY_NUMPAD_LESS	78
#  define KEY_Q		12
#  define KEY_W		13
#  define KEY_E		14
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_LEFT	123
#  define KEY_RIGHT	124
#  define KEY_UP	126
#  define KEY_DOWN	125
# endif

# define ABS(x) (x < 0) ? -x : x

# define DEG(x) (x * 180.0 / M_PI)
# define RAD(x) (x * M_PI / 180.0)

//typedef float t_matrix4[4][4];
typedef float t_matrix4[16]; // t_mat4x4

typedef struct	s_vector2
{
	float		x;
	float		y;
}				t_vector2; // t_vec2f

// t_vec2i

typedef struct	s_vector3
{
	float		x;
	float		y;
	float		z;
}				t_vector3; // t_vec3f

typedef struct	s_vector4
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vector4; // t_vec4f

typedef struct	s_triangle
{
	t_vector3	a;
	t_vector3	b;
	t_vector3	c;
}				t_triangle; // t_tri

// typedef t_vec3f[3] t_tri;

typedef struct	s_vert
{
	t_vector3	coord;
	int			color;
}				t_vert;

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
	float		*zbuffer;
	t_grid		*grid;
	t_triangle	*cube;
	int			col;
	float		near; // camera value
	float		far; // camera value
	t_matrix4	*world;
	t_matrix4	*worldToCamera;
	t_matrix4	*view;
	t_matrix4	*projection;
	int			width; // image (or framebuffer) value
	int			height; // image value
	float		aspect; // image or canvas value
	float		canvasS; // canvas (or screen) value
	float		canvasW; // canvas value
	float		canvasH; // canvas value
	float		canvasT; // canvas value
	float		canvasB; // canvas value
	float		canvasL; // canvas value
	float		canvasR; // canvas value
}				t_mlx_sess;

/*
**	FILES
*/

t_vert	**get_vertmap_from_file(char *path, int *x, int *y);

/*
**	DRAWING
*/

void	draw_line(t_mlx_sess *, t_vector2 *, t_vector2 *);
void	draw_square(t_mlx_sess *, int color, t_vector2 *, t_vector2 *);
//void	draw_line(t_mlx_sess *, t_vector3, t_vector3);
void	draw_picture(t_mlx_sess *);

void	clear_canvas(t_mlx_sess *, int);

void	cube(t_triangle *);
void	init_grid(t_grid *, int, int);
void	init_grid_from_vertmap(t_grid *, t_vert **vertmap, int, int);
void	draw_3dgrid(t_mlx_sess *);

void	set_image_pixel(t_mlx_sess *p, t_image * img, int color, int x, int y);

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

/*
**	GNL
*/
typedef struct	s_parser
{
	int		fd;
	long	bs;
	char	*buf;
}				t_parser;

int				get_next_line(int const fd, char **line);

# ifdef DEBUG
void	output_image_info(t_image *image);
# endif
#endif
