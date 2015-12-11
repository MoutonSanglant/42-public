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
}			t_tetriminos;

void	fillit_error(void);
void	get_tetriminos();

char ***g_tetri_table = {
	{ "##", "##", "" },
	{ "####", "" },
	{ "#", "#", "#", "#", "" },
	{ ".##", "##.", "" },
	{ "#.", "##", ".#", "" },
	{ "##.", ".##", "" },
	{ ".#", "##", "#.", "" },
	{ "" }
	{ "###", ".#.", "" },
	{ "#.",	"##", "#.", "" },
	{ }
}

#endif
