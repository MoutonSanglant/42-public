/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tetriminos_from_buffer.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/18 19:56:10 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/12 16:17:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/*
** TODO: free all the mallocs and ft_lstnew !!
*/
t_list *get_tetriminos_from_buffer(char *buffer)
{
	unsigned short	width;
	unsigned short	height;
	unsigned int	mask;
	char			*buffer_start;
	t_list			*list;
	t_list			*list_start;
	t_tetrimino		*tetrimino;

	list = NULL;
	mask = 0;
	height = 0;
	buffer_start = buffer;
	list_start = NULL;
	while (*buffer)
	{
		width = 0;
		while (*buffer != '\n')
		{
			if (width > 3 || height > 3)
				buffer_error(buffer_start);
			if (*buffer == '#')
				mask |= 1 << (width + (height * 4));
			else if (*buffer != '.')
				buffer_error(buffer_start);
			width++;
			buffer++;
		}
		if (width < 4)
			buffer_error(buffer_start);
		height++;
		buffer++;
		if (*buffer == '\n') /* || '\0' */
		{
			if (buffer[1] == '\0')
				error();
			/*
			** TODO: check if there is more than one \n between patterns
			** TODO: also check if there are extra \n after last pattern
			*/
			tetrimino = (t_tetrimino *)malloc(sizeof(t_tetrimino));
			if (!tetrimino)
				error();
			tetrimino->pattern_id = get_pattern_id(mask);
			tetrimino->h_shift = 0;
			tetrimino->v_shift = 0;
			if (list)
			{
				list->next = ft_lstnew(tetrimino, sizeof(*tetrimino));
				list = list->next;
			}
			else
			{
				list = ft_lstnew(tetrimino, sizeof(*tetrimino));
				list_start = list;
			}
			mask = 0;
			height = 0;
			buffer++;
		}
	}
	tetrimino = (t_tetrimino *)malloc(sizeof(t_tetrimino));
	if (!tetrimino)
		error();
	tetrimino->pattern_id = get_pattern_id(mask);
	tetrimino->h_shift = 0;
	tetrimino->v_shift = 0;
	if (list)
	{
		list->next = ft_lstnew(tetrimino, sizeof(*tetrimino));
		list = list->next;
	}
	else
		list = ft_lstnew(tetrimino, sizeof(*tetrimino));

	if (!list_start)
		list_start = list;

	return (list_start);
}
