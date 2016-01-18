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
	void	*sess;
	void	*win;
	t_image	*img;
	int		col;
}				t_mlx_sess;

typedef struct	s_vector2
{
	int		x;
	int		y;
}				t_vector2;

typedef struct	s_vector3
{
	int		x;
	int		y;
	int		z;
}				t_vector3;

void	draw_line(t_mlx_sess *, t_vector2 *, t_vector2 *);
void	draw_square(t_mlx_sess *, t_vector2 *, t_vector2 *);
//void	draw_line(t_mlx_sess *, t_vector3, t_vector3);
void	draw_picture(t_mlx_sess *);

void	draw_3dgrid(t_mlx_sess *);

void	set_image_pixel(t_image * img, int color, int x, int y);


# ifdef DEBUG
void	output_image_info(t_image *image);
# endif
#endif
