/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mabuchwa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/08 15:01:46 by mabuchwa          #+#    #+#             */
/*   Updated: 2016/01/09 16:28:42 by mabuchwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H

# define BUF_SIZE 21
# define TAB (tab + value.n_tetri)

# include <string.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

typedef struct		s_pos
{
	int				x[4];
	int				y[4];
	char			letter;
	int				nb_tetri;
}					t_pos;

typedef struct		s_val
{
	int				sd;
	int				n_tetri;
}					t_val;

int					ft_check_file(char *buf, int i, int nl);
void				ft_bzero(void *s, size_t n);
void				ft_get_coor(char *buf, t_pos *tab, int nb_fig);
void				ft_up_left(t_pos *tab, int nb_fig);
void				ft_get_size(char **board, t_pos *tab, int side);
void				ft_putstr(const char *s);
void				*ft_memset(void *b, int c, size_t len);
void				ft_print_board(char **board, int side);
void				ft_resolution(char **board, int side, t_pos *tab,
					int num_tetri);

#endif
