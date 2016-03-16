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

# define PROGRAM_NAME "ls"
# define VALID_FLAGS "Ralrt"
# define MONTH_IN_SECS 2628000

# ifdef LINUX
#  define ST_MTIM st_mtim
#  define MAJOR major
#  define MINOR minor
# else
#  define ST_MTIM st_mtimespec
#  define MAJOR(x) (x >> 24)
#  define MINOR(x) ((x << 8) >> 8)
# endif

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
	void		(*print_fn)(const struct s_ls_datas *, t_file_datas *);
	int			(*sort_fn)(void *, void *);
	int			(*time_sort_fn)(void *, void *);
}					t_ls_datas;

/*
********************************************************************************
**							:: Init functions ::							   *
********************************************************************************
*/

/*
**								: fetch_file_datas.c :
*/
void				fetch_args(int argc, char **argv, t_ls_datas *ls_datas);

/*
********************************************************************************
**							:: Destroy functions ::							   *
********************************************************************************
*/

/*
**								: clear_ls_datas.c :
*/
void				clear_ls_datas(t_ls_datas *ls_datas);

/*
********************************************************************************
**						:: File/Directories functions ::					   *
********************************************************************************
*/

/*
**								: fetch_file_datas.c :
*/
t_list				*fetch_file_datas(t_ls_datas *ls_datas,
										t_file_datas *file,
										const char *folder_name);
/*
**								: file_mode_str.c :
*/
void				file_mode_str(mode_t mode, char *str);

/*
**								: read_dir.c :
*/
int					read_dir(t_ls_datas *ls_datas, t_file_datas *file_datas,
								const char *f_name);

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
								t_file_datas *file_data);
void				print_detailed_line(const t_ls_datas *ls_datas,
										t_file_datas *file_data);

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
int					error_path(const char *s);
void				error_unimplemented(t_ls_datas *ls_datas);
void				error_usage(int c, t_ls_datas *ls_datas);
void				error_memalloc(t_ls_datas *ls_datas);

#endif
