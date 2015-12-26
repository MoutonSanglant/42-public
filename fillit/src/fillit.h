/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 21:06:30 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/10 21:06:30 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

#define DEBUG 0

# include <libft.h>
# include <fcntl.h>
# include <unistd.h>

typedef unsigned short t_mask16;
typedef long long unsigned int t_mask64;

/*
** Since we know all the possible patterns, we can set a pattern
** map and pull from this map whenever a tetrimino is needed
** according to an id.
*/
typedef struct		s_tetrimino
{
	unsigned char	pattern_id;
	unsigned char	h_shift;
	unsigned char	v_shift;
}			t_tetrimino;

typedef struct		s_tetri_masks
{
	t_mask64	tetri;
	t_mask64	shifted;
	t_mask64	last;
	t_mask64	shift;
}			t_tetri_masks;

typedef struct		s_grid_mask
{
	t_mask64	tetri;
	t_mask64	right;
	t_mask64	bottom;
	t_mask64	fill;
}			t_grid_mask;

typedef struct		s_bf_params
{
	t_list	*list;
	t_grid_mask	*grid;
}			t_bf_params;

char	*read_tetri_file(char*);
t_list	*get_tetriminos_from_buffer(char*);

void	fillit(t_list*);
t_mask64	bruteforce(t_bf_params*, size_t, t_list*);
void	print_grid(size_t, t_list*);

char	get_pattern_id(t_mask16);
void	delelem(void *content, size_t content_size);

void	buffer_error(char*);
void	error(void);

extern t_mask16	g_mask_table[19][9];
extern char				*g_pattern_table[19][5];

#endif
