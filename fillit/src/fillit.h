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

# include <libft.h>
# include <fcntl.h>
# include <unistd.h>

/*
** Since we know all the possible patterns, we can set a pattern
** map and pull from this map whenever a tetrimino is needed
** according to an id.
*/
typedef struct		s_tetriminos
{
	char	letter;
	char	pattern_id;
	unsigned char	h_shift;
	unsigned char	v_shift;
}			t_tetriminos;

typedef long long unsigned int t_mask;

void	fillit(t_list *tetri_list);
char	*read_tetri_file(char *);
t_list	*get_tetriminos_from_buffer(char *);
char	get_pattern_id(unsigned short mask);
void	buffer_error(char *);
void	error(void);

extern unsigned short	g_mask_table[19][9];
extern char				*g_pattern_table[19][5];

#endif
