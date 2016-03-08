/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keypress.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/04 14:14:47 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/09 12:13:51 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		keypress(int key, void *p)
{
	t_mlx_sess	*sess;

	sess = (t_mlx_sess *)p;
	if (key == KEY_ESCAPE)
	{
		destroy_mlx_sess(sess);
		exit(0);
	}
	return (0);
}
