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

typedef long long unsigned int t_mask;

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

typedef struct		s_bruteforce_params
{
	t_list	*final_list;
	t_mask	grid_mask;
	t_mask	right_mask;
	t_mask	bottom_mask;
	t_mask	full_mask;
}			t_bruteforce_params;

void	delelem(void *content, size_t content_size);

void	fillit(t_list *tetri_list);
t_mask	bruteforce(t_bruteforce_params *, size_t, t_list*);
char	*read_tetri_file(char *);
t_list	*get_tetriminos_from_buffer(char *);
char	get_pattern_id(unsigned short mask);
void	print_grid(size_t w, t_list *final_list);

void	buffer_error(char *);
void	error(void);

extern unsigned short	g_mask_table[19][9];
extern char				*g_pattern_table[19][5];

#endif
