/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_2048.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/30 17:37:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/30 22:00:53 by framel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_2048_H
# define GAME_2048_H

# include <time.h>
# include <ncurses.h>
# include <includes/libft.h>

# define GAME_ERR_MSG "Window is too small !!"
# define GAME_MIN_Y 26
# define GAME_MIN_X 52

# define MENU_TITLE "Menu"
# define MENU_WIDTH(w) w / 2
# define MENU_HEIGHT(h) 8 
# define MENU_X(lines, x) (lines - x / 2) / 2
# define MENU_Y(cols, y) (cols - y / 2) / 2

# define GAME_TITLE "2048"
# define GAME_WIDTH(w) (w - w % 8) / 2 - 3
# define GAME_HEIGHT(h) (h - h % 8) / 2 - 3
# define GAME_X(lines, x) (lines - x / 2) / 2
# define GAME_Y(cols, y) (cols - y / 2) / 2

# define OPTIONS_TITLE "Options"
# define OPTIONS_WIDTH(w) w / 2
# define OPTIONS_HEIGHT(h) h / 2
# define OPTIONS_X(lines, x) (lines - x / 2) / 2
# define OPTIONS_Y(cols, y) (cols - y / 2) / 2

enum e_const
{
	WIN_VALUE = 2048
};

typedef struct	s_sess
{
	int		row;
	int		col;
	size_t	*board;
	size_t	board_width;
	size_t	board_size;
	int		player_input;
	int		input;
}				t_sess;

typedef struct	s_win
{
	WINDOW	*self;
	int		x;
	int		y;
	int		height;
	int		width;
	int		color;
	void	*loop;
	char	*title;
	char	*caption;
	char	*caption2;
	char	*blank_line;
}				t_win;

typedef struct	s_vec2
{
	int		x;
	int		y;
}				t_vec2;

typedef struct s_task	t_task;

typedef void	(*t_loop_func)(t_sess *, t_win **, t_task *);

struct			s_task
{
	t_loop_func	loop_f;
};

/*
**	EVENTS
*/
void			input_handler(t_sess *, t_win **p_win,
						int (*callback)(t_sess *, t_win **, int, t_task *),
						t_task *);

/*
**	WINDOWS
*/
t_win			*create_window(t_vec2 coord, int starty,
								int startx, char *title);
void			destroy_window();
void			refresh_window(t_win *win);
void			swap_windows(t_win **p_win, t_vec2 row_col,
								t_vec2 coord, char *title);

void			putline(t_sess *sess, t_win *win);
void			putcol(t_sess *sess, t_win *win);

/*
**	LOOPS
*/
void			menu_loop(t_sess *sess, t_win **p_win, t_task *loop_func);
void			game_loop(t_sess *sess, t_win **p_win, t_task *loop_func);
void			options_loop(t_sess *sess, t_win **p_win, t_task *loop_func);

/*
**	GAME
*/

void			restart_game(t_sess *sess);
void			board_step(t_sess *sess, t_win **p_win);
int				fill_random_tile(t_sess *sess, int salt);
int				possible_moves(t_sess *sess, int test);

#endif
