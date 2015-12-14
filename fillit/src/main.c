/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/10 15:19:26 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/13 18:57:07 by tdefresn         ###   ########.fr       */
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

unsigned short g_mask_table[19][9] = {
	{ 0x33, 0x66, 0xcc, 0x330, 0x660, 0xcc0, 0x3300, 0x6600, 0xcc00 },
	{ 0xf, 0xf0, 0xf00, 0xf000 },
	{ 0x1111, 0x2222, 0x4444, 0x8888 },
	{ 0x36, 0x6c, 0x360, 0x6c0, 0x3600, 0x6c00 },
	{ 0x231, 0x462, 0x8c4, 0x2310, 0x4620, 0x8c40 },
	{ 0x63, 0xc6, 0x630, 0xc60, 0x6300, 0xc600 },
	{ 0x132, 0x264, 0x4c8, 0x1320, 0x2640, 0x4c80 },
	{ 0x311, 0x622, 0xc44, 0x3110, 0x6220, 0xc440 },
	{ 0x17, 0x2e, 0x170, 0x2e0, 0x1700, 0x2e00 },
	{ 0x223, 0x446, 0x88c, 0x2230, 0x4460, 0x88c0 },
	{ 0x74, 0xe8, 0x740, 0xe80, 0x7400, 0xe800 },
	{ 0x322, 0x644, 0xc88, 0x3220, 0x6440, 0xc880 },
	{ 0x71, 0xe2, 0x710, 0xe20, 0x7100, 0xe200 },
	{ 0x113, 0x226, 0x44c, 0x1130, 0x2260, 0x44c0 },
	{ 0x47, 0x8e, 0x470, 0x8e0, 0x4700, 0x8e00 },
	{ 0x27, 0x4e, 0x270, 0x4e0, 0x2700, 0x4e00 },
	{ 0x232, 0x464, 0x8c8, 0x2320, 0x4640, 0x8c80 },
	{ 0x72, 0xe4, 0x720, 0xe40, 0x7200, 0xe400 },
	{ 0x131, 0x262, 0x4c4, 0x1310, 0x2620, 0x4c40 }
};

char *g_pattern_table[19][5] = {
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
	{ "###", "..#", NULL },
	{ "###", ".#.", NULL },
	{ ".#", "##", ".#", NULL },
	{ ".#.", "###", NULL },
	{ "#.", "##", "#.", NULL }
};

void	__print_patterns(t_list *elem)
{
	t_tetriminos	*tetri;
	int	i;
	char	*str;
	
	tetri = (t_tetriminos *)elem->content;
	i = 0;
	while ((str = g_pattern_table[(int)tetri->pattern_id][i]))
	{
		while (*str)
		{
			if (*str == '#')
				ft_putchar(tetri->letter);
			else
				ft_putchar('.');
			str++;
		}
		ft_putchar('\n');
		//ft_putendl(str);
		i++;
	}
	ft_putchar('\n');
}

int		main(int argc, char **argv)
{
	char	*file_buffer;
	t_list	*tetri_list;

	if (argc != 2)
		error();
	file_buffer = read_tetri_file(argv[1]);
	if (!file_buffer)
		error();
	tetri_list = get_tetriminos_from_buffer(file_buffer);
	ft_memdel((void **)&file_buffer);
	if (tetri_list)
	{
		//ft_lstiter(tetri_list, &__print_patterns);
		fillit(tetri_list);
	}
	return (0);
}
