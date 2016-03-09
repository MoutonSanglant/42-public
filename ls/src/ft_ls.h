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
# include <sys/stat.h>
# include <pwd.h>
# include <grp.h>
# include <time.h>
# include <includes/libft.h>

# define VALID_FLAGS "Ralrt"

typedef enum		e_ls_flags
{
	FLAG_NONE = 0x0,
	FLAG_L = 0x1,
	FLAG_R = 0x2,
	FLAG_BIG_R = 0x4,
	FLAG_A = 0x8,
	FLAG_T = 0x10
}					t_ls_flags;

typedef struct		s_file_datas
{
	char		*name;
	//void		*datas;
	struct stat	st_stat;
}					t_file_datas;

/*
**	Padding: 8 (*)
**	  8
**	+ 8
**	+ 4
**	===
**	 20
**	(4 bytes losts)
*/

typedef struct		s_ls_datas
{
	DIR			*p_dir;
	t_list		*folders;
	t_ls_flags	flags;
	void		(*print_fn)(const t_file_datas *);
	int			(*sort_fn)(void *, void *);
}					t_ls_datas;

void			read_args(int argc, char **argv, t_ls_datas *ls_datas);

int		read_dir(const char *folder_name, t_ls_datas *ls_datas);

void	print_line(const t_file_datas *file_data);
void	print_detailed_line(const t_file_datas *file_data);

void				error_unimplemented();
int					error_path(const char *s);
void				error_usage(int c);

#endif
