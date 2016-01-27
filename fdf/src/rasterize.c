/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterize.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/27 12:41:37 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/27 14:00:48 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	edge_function(const t_vec2f *a, const t_vec3f *b, const t_vec2f *c)
{
	return ((c.x - a.x) * (b.y - a.y) * (b.x - a.x) >= 0);
}

void		rasterize(t_tri *triangle)
{
	t_vec2f	p;
	int		inside;

	inside &= edge_funcion(triangle[0], t_triangle[1], p);
	inside &= edge_funcion(triangle[1], t_triangle[2], p);
	inside &= edge_funcion(triangle[2], t_triangle[0], p);

	if (inside)
	{
		// point is inside
	}
}
