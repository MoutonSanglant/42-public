/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/29 01:43:16 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/29 01:43:16 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

typedef enum	e_ls_flags
{
	FLAG_L = 0x1,
	FLAG_R = 0x2,
	FLAG_BIG_R = 0x4,
	FLAG_A = 0x8,
	FLAG_T = 0x10
}				t_ls_flags;

#endif
