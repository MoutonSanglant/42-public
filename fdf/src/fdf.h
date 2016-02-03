/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/26 01:00:57 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 15:52:34 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>

# include <includes/libft.h>

# define BUFF_SIZE 32
# define WHITE 0x00ffffff
# define RED 0x00ff0000
# define GREEN 0x0000ff00
# define BLUE 0x000000ff

/*
** BONUS
*/
# ifdef BONUS
#  include <float.h>
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
#  define KEY_O		111
#  define KEY_P		112
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
#  define KEY_PAGE_UP	65365
#  define KEY_PAGE_DOWN	65366

# else
#  include "../includes/mlx.h"
#  define KEYPRESSMASK	(1L<<0)
#  define KEYPRESS	2

/*
** the '+' key is under the '-' key on mac keyboard
*/
#  define KEY_NUMPAD_MORE	69
#  define KEY_NUMPAD_LESS	78
#  define KEY_O		31
#  define KEY_P		35
#  define KEY_Q		12
#  define KEY_W		13
#  define KEY_E		14
#  define KEY_A		0
#  define KEY_S		1
#  define KEY_D		2
#  define KEY_B		11
#  define KEY_LEFT	123
#  define KEY_RIGHT	124
#  define KEY_UP	126
#  define KEY_DOWN	125
#  define KEY_PAGE_UP	116
#  define KEY_PAGE_DOWN	121
# endif

# define ABS(x) (x < 0) ? -x : x

# define DEG(x) (x * 180.0 / M_PI)
# define RAD(x) (x * M_PI / 180.0)

/*
**	Matrices are in row-major columns
*/
typedef float	t_mat4x4[16];

typedef struct	s_vec2
{
	int			x;
	int			y;
}				t_vec2;

typedef struct	s_vec2ui32
{
	uint32_t	x;
	uint32_t	y;
}				t_vec2ui32;

typedef struct	s_vec2f
{
	float		x;
	float		y;
}				t_vec2f;

typedef struct	s_vec3f
{
	float		x;
	float		y;
	float		z;
}				t_vec3f;

typedef struct	s_vec4f
{
	float		x;
	float		y;
	float		z;
	float		w;
}				t_vec4f;

typedef struct	s_color
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}				t_color;

typedef struct	s_vert
{
	t_vec3f		coord;
	t_color		color;
}				t_vert;

typedef t_vert	t_tri[3];

typedef struct	s_grid
{
	int		width;
	int		height;
	t_tri	*triangles;
}				t_grid;

typedef struct	s_image
{
	void	*img;
	char	*data;
	char	*filename;
	int		sl;
	int		bpp;
	int		endian;
}				t_image;

typedef struct	s_camera
{
	float	angle_of_view;
	float	aspect;
	float	far;
	float	near;
	float	top;
	float	bottom;
	float	left;
	float	right;
}				t_camera;

typedef struct	s_mlx_sess
{
	void		*sess;
	void		*win;
	t_image		*img;
	float		*zbuffer;
	t_grid		*grid;
	int			col;
	t_camera	camera;
	t_mat4x4	*world;
	t_mat4x4	*world_to_camera;
	t_mat4x4	*view;
	t_mat4x4	*projection;
	uint32_t	width;
	uint32_t	height;
	int			need_update;
	t_mat4x4	m_model;
	float		line_width;
	int			lines_color;
	int			faces_color;
	int			bg_color;
	float		map_height;
	int			bresenham;
}				t_mlx_sess;

typedef struct	s_bresenham
{
	t_vec2ui32	xy;
	int			e;
	int			x1;
	int			x2;
	int			y1;
	int			y2;
	int			dx;
	int			dy;
	int			incx;
	int			incy;
	int			inc1;
	int			inc2;
}				t_bresenham;

/*
**	FILES
*/

int				count_file_lines(char *path);
t_vert			**get_vertmap_from_file(char *path, int *x, int *y);

/*
**	RENDERING
*/

void			draw_3dgrid(t_mlx_sess *sess);
void			rasterize(t_mlx_sess *p, t_tri *triangle);

/*
**	DRAWING
*/

void			bresenham_draw_line(t_mlx_sess *sess, t_vec2 *from, t_vec2 *to);
void			draw_square(t_mlx_sess *sess, int color,
							t_vec2f *from, t_vec2f *to);
void			draw_picture(t_mlx_sess *sess);

void			clear_canvas(t_mlx_sess *sess, int color);
void			set_image_pixel(t_mlx_sess *sess, t_image *img, int color,
								t_vec2ui32 xy);

/*
**	INITIALISATIONS
*/

void			init_grid(t_grid *grid, int width, int height);
void			init_grid_from_vertmap(t_grid *grid, t_vert **vertmap,
										int width, int height);

/*
**	MATRIX
*/

void			identity_matrix4(t_mat4x4 *mat);
void			inverse_matrix4(t_mat4x4 *in_mat, t_mat4x4 *out_mat);
void			translation_matrix4(t_mat4x4 *mat, t_vec3f vec);
void			scaling_matrix4(t_mat4x4 *mat, t_vec3f vec);
void			rotation_x_matrix4(t_mat4x4 *mat, float alpha);
void			rotation_y_matrix4(t_mat4x4 *mat, float alpha);
void			rotation_z_matrix4(t_mat4x4 *mat, float alpha);
void			perspective_projection_matrix4(t_mat4x4 *mat, t_camera *camera);
void			orthographic_projection_matrix4(t_mat4x4 *mat,
												t_camera *camera);

void			copy_matrix4(t_mat4x4 *dst, const t_mat4x4 *src);
void			transpose_matrix4(t_mat4x4 *mat);
void			matrix4_product(t_mat4x4 *mat_b, t_mat4x4 *out);
t_vec3f			apply_matrix4(t_vec3f vec, t_mat4x4 *mat);

/*
**	CAMERAS
*/

void			set_orthographic_camera(t_mlx_sess *sess);
void			set_perspective_camera(t_mlx_sess *sess);

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

/*
**	EXTRA
*/

void			change_grid_z(t_grid *grid, float factor);

# ifdef DEBUG

#  define LINE_HEIGHT 18

void			output_image_info(t_image *image);
void			draw_debug_gui(t_mlx_sess *sess);
# endif
#endif
