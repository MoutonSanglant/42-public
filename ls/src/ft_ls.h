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
# define MONTH_IN_SECS 2628000

typedef enum		e_ls_flags
{
	FLAG_NONE = 0x0,
	FLAG_L = 0x1,
	FLAG_R = 0x2,
	FLAG_BIG_R = 0x4,
	FLAG_A = 0x8,
	FLAG_T = 0x10,
	_FLAG_PRINT_FOLDERS_NAME = 0x20
}					t_ls_flags;

typedef struct		s_file_datas
{
	char			*name;
	char			*pathname;
	struct stat		st_stat;
}					t_file_datas;

/*
**	Padding: 8 (*)
**	  8
**	+ 8
**  + 8
**	+ 4
**  + 8
**  + 8
**	===
**	 44 (48)
**	(4 bytes losts)
*/

typedef struct		s_ls_datas
{
	DIR			*p_dir;
	t_list		*directories;
	t_list		*files;
	t_ls_flags	flags;
	int			col_user_width;
	int			col_group_width;
	int			col_links_width;
	int			col_size_width;
	size_t		total_blocks_count;
	void		(*print_fn)(const struct s_ls_datas *, const t_file_datas *);
	int			(*sort_fn)(void *, void *);
	int			(*time_sort_fn)(void *, void *);
}					t_ls_datas;

void				fetch_args(int argc, char **argv, t_ls_datas *ls_datas);
int					read_dir(const char *folder_name, t_ls_datas *ls_datas);
t_list				*fetch_file_datas(t_ls_datas *ls_datas,
										const char *file_name,
										const char *folder_name);

/*
********************************************************************************
**							:: List functions ::							   *
********************************************************************************
*/

/*
**								: list_fn.c :
*/
void				list_files(t_ls_datas *ls_datas, t_list *file_list,
							const char *folder_name);
int					list_directories(t_ls_datas *ls_datas);

/*
********************************************************************************
**							:: Mutable functions ::							   *
********************************************************************************
*/

/*
**								: print_fn.c :
*/
void				print_one(const t_ls_datas *ls_datas,
								const t_file_datas *file_data);
void				print_detailed_line(const t_ls_datas *ls_datas,
										const t_file_datas *file_data);

/*
**								: sort_fn.c :
*/
int					sort_lexicographic (void *struct1, void *struct2);
int					sort_antilexicographic (void *struct1, void *struct2);
int					sort_time (void *struct1, void *struct2);
int					sort_time_reverse (void *struct1, void *struct2);

/*
********************************************************************************
**							:: Error functions ::							   *
********************************************************************************
*/

/*
**								: errors.c :
*/
void				error_unimplemented();
int					error_path(const char *s);
void				error_usage(int c);

#endif
