/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hex_to_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/12 11:43:58 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/12 11:44:12 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

float		hex_to_float(char *hex)
{
	char	a;
	char	b;

	a = 0;
	b = 0;
	if (hex[0] >= 'A' && hex[0] <= 'F')
		a = hex[0] - 'A' + 10;
	else if (hex[0] >= 'a' && hex[0] <= 'f')
		a = hex[0] - 'a' + 10;
	else if (hex[0] >= '0' && hex[0] <= '9')
		a = hex[0] - '0';
	if (hex[1] >= 'A' && hex[1] <= 'F')
		b = hex[1] - 'A' + 10;
	else if (hex[1] >= 'a' && hex[1] <= 'f')
		b = hex[1] - 'a' + 10;
	else if (hex[1] >= '0' && hex[1] <= '9')
		b = hex[1] - '0';
	return ((float)((a * 16) + b) / 255);
}
