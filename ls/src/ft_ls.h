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

# include <stdlib.h>
# include <dirent.h>
# include <includes/libft.h>

# define VALID_FLAGS "Ralrt"

typedef enum	e_ls_flags
{
	FLAG_NONE = 0x0,
	FLAG_L = 0x1,
	FLAG_R = 0x2,
	FLAG_BIG_R = 0x4,
	FLAG_A = 0x8,
	FLAG_T = 0x10
}				t_ls_flags;

/*
**	Padding: 8 (*)
**	  8
**	+ 8
**	+ 4
**	===
**	 20
**	(4 bytes losts)
*/

typedef struct	s_ls_datas
{
	DIR			*p_dir;
	t_list		*path;
	t_ls_flags	flags;
}				t_ls_datas;

int		error_path(const char *s);
void	error_usage(int c);

#endif
