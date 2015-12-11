/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 15:19:26 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/11 14:11:05 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** pattern ids
** 0 -> square
** 1 -> h-bar
** 2 -> v-bar
** 3 -> h-s
** 4 -> v-s
** 5 -> h-flipped-s
** 6 -> v-flipped-s
** 7 -> l
** 8 -> l-90
** 9 -> l-180
** 10 -> l-270
** 11 -> flipped-l
** 12 -> flipped-l-90
** 13 -> flipped-l-180
** 14 -> flipped-l-270
** 15 -> T
** 16 -> T-90
** 17 -> T-180
** 18 -> T-270
*/

char *g_pattern_table[18][5] = {
	{ "##", "##", NULL },
	{ "####", NULL },
	{ "#", "#", "#", "#", NULL },
	{ ".##", "##.", NULL },
	{ "#.", "##", ".#", NULL },
	{ "##.", ".##", NULL },
	{ ".#", "##", "#.", NULL },
	{ "#.",	"#.", "##", NULL },
	{ "###", "#..", NULL },
	{ "##",	".#", ".#", NULL },
	{ "..#", "###", NULL },
	{ ".#",	".#", "##", NULL },
	{ "#..", "###", NULL },
	{ "##",	"#.", "#.", NULL },
	{ "###", "..#", NULL }
};

int		main(int argc, char **argv)
{
	char *file_buffer;
	if (argc != 2)
		error();
	file_buffer = read_tetri_file(argv[1]);
	if (!file_buffer)
		error();
	get_tetriminos_from_buffer(file_buffer);
	return (0);
}
