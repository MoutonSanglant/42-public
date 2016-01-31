/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/03 12:41:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/03 12:41:49 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	cube(t_tri *cube)
{
	t_vec3f points[8];

	// A
	points[0].x = -.5f;
	points[0].y = -.5f;
	points[0].z = -.5f;
	// B
	points[1].x = .5f;
	points[1].y = -.5f;
	points[1].z = -.5f;
	// C
	points[2].x = .5f;
	points[2].y = .5f;
	points[2].z = -.5f;
	// D
	points[3].x = -.5f;
	points[3].y = .5f;
	points[3].z = -.5f;
	// E
	points[4].x = -.5f;
	points[4].y = -.5f;
	points[4].z = .5f;
	// F
	points[5].x = .5f;
	points[5].y = -.5f;
	points[5].z = .5f;
	// G
	points[6].x = .5f;
	points[6].y = .5f;
	points[6].z = .5f;
	// H
	points[7].x = -.5f;
	points[7].y = .5f;
	points[7].z = .5f;

	cube[0][0].coord = points[1];
	cube[0][1].coord = points[3];
	cube[0][2].coord = points[0];
	cube[1][0].coord = points[1];
	cube[1][1].coord = points[2];
	cube[1][2].coord = points[3];

	cube[2][0].coord = points[5];
	cube[2][1].coord = points[2];
	cube[2][2].coord = points[1];
	cube[3][0].coord = points[5];
	cube[3][1].coord = points[6];
	cube[3][2].coord = points[2];

	cube[4][0].coord = points[4];
	cube[4][1].coord = points[6];
	cube[4][2].coord = points[5];
	cube[5][0].coord = points[4];
	cube[5][1].coord = points[7];
	cube[5][2].coord = points[6];

	cube[6][0].coord = points[0];
	cube[6][1].coord = points[7];
	cube[6][2].coord = points[4];
	cube[7][0].coord = points[0];
	cube[7][1].coord = points[3];
	cube[7][2].coord = points[7];

	cube[8][0].coord = points[2];
	cube[8][1].coord = points[7];
	cube[8][2].coord = points[3];
	cube[9][0].coord = points[2];
	cube[9][1].coord = points[6];
	cube[9][2].coord = points[7];

	cube[10][0].coord = points[1];
	cube[10][1].coord = points[0];
	cube[10][2].coord = points[4];
	cube[11][0].coord = points[1];
	cube[11][1].coord = points[4];
	cube[11][2].coord = points[5];
}
