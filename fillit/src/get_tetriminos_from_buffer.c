/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tetriminos_from_buffer.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/11 14:12:33 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/11 14:42:31 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

void get_tetriminos_from_buffer(char *buffer)
{
	int		count;
	char	*buffer_start;

	/*
	** Detect a tetrimino
	*/
	buffer_start = buffer;
	while (*buffer)
	{
		count = 0;
		while (*buffer != '\n')
		{
			if (count > 3)
				buffer_error(buffer_start);
			count++;
			buffer++;
		}
		buffer++;
	}
}
