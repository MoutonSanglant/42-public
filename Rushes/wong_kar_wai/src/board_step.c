/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   board_step.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/31 12:57:24 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/31 23:22:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game_2048.h"


	static void		player_win(t_win **p_win)
	{
		(*p_win)->caption = ft_strdup("Congratulation ! You won the game !");
		(*p_win)->caption2 = ft_strdup("");
		refresh_window(*p_win);
	}

	static int		possible_move(t_sess *sess)
	{
		size_t		x;
		size_t		y;
		size_t		value;
		int			test;

		test = 0;
		y = 0;
		while (y < sess->board_width)
		{
			x = 0;
			while (x < sess->board_width)
			{
				value = sess->board[x + y * sess->board_width];
				if (x + 1 < sess->board_width)
				{
					if (value == sess->board[x + 1 + y * sess->board_width])
						test = 1;
				}
				if (y + 1 < sess->board_width)
				{
					if (value == sess->board[x + (y + 1) * sess->board_width])
						test = 1;
				}
				x++;
			}
			y++;
		}
		if (test == 0)
			return (0);

		return (1);
	}



void			board_step(t_sess *sess, t_win **p_win)
{
	int		i;
	int		j;
	size_t		col;
	size_t		row;
	size_t		mod;
	int			test;
	int		*locked_indexes;

	locked_indexes = (int *)ft_memalloc(sizeof(int) * 16);
	locked_indexes = ft_memset(locked_indexes, 0, 16);

	test = 0;
	if (sess->player_input == KEY_DOWN)
	{
		i = sess->board_size - 1;
		while (i >= 0)
		{
			if (sess->board[i] != 0)
			{
				col = i / sess->board_width;
				row = i % sess->board_width;

				j = i;
				j += (i + 1 > (int)sess->board_size) ? 0 : 1;
				while (sess->board[j] == 0 && (size_t)j < col * sess->board_width + 3)
					j++;

				//j = col * sess->board_width + 3;
				while (j % sess->board_width > row)
				{
					mod = j % sess->board_width;
					if (sess->board[i + (mod - row)] == 0)
					{
						sess->board[i + (mod - row)] = sess->board[i];
						sess->board[i] = 0;
						test = 1;
						break ;
					}
					else if (sess->board[i + (mod - row)] == sess->board[i])
					{
						test = 1;
						if (locked_indexes[i + (mod - row)])
						{
							sess->board[i + (mod - row - 1)] = sess->board[i];
							sess->board[i] = 0;
							break;
						}
						locked_indexes[i + (mod - row)] = 1;
						sess->board[i + (mod - row)] *= 2;
						sess->board[i] = 0;
						if (sess->board[i + (mod - row)] == WIN_VALUE)
							player_win(p_win);
						break ;
					}
					j--;
				}
			}
			i--;
		}
	}
	else if (sess->player_input == KEY_UP)
	{
		i = 0;
		while ((size_t)i < sess->board_size)
		{
			if (sess->board[i] != 0)
			{
				col = i / sess->board_width;
				row = i % sess->board_width;

				j = i;
				j -= (i - 1 < 0) ? 0 : 1;
				while (sess->board[j] == 0 && (size_t)j > col * sess->board_width)
					j--;

				while (j % sess->board_width < row) // > row
				{
					mod = j % sess->board_width;
					if (sess->board[i + (mod - row)] == 0)
					{
						sess->board[i + (mod - row)] = sess->board[i];
						sess->board[i] = 0;
						test = 1;
						break ;
					}
					else if (sess->board[i + (mod - row)] == sess->board[i])
					{
						test = 1;
						if (locked_indexes[i + (mod - row)])
						{
							sess->board[i + (mod - row + 1)] = sess->board[i];
							sess->board[i] = 0;
							break;
						}
						locked_indexes[i + (mod - row)] = 1;
						sess->board[i + (mod - row)] *= 2;
						sess->board[i] = 0;
						if (sess->board[i + (mod - row)] == WIN_VALUE)
							player_win(p_win);
						break ;
					}
					j++; // j--
				}
			}
			i++;
		}
	}
	else if (sess->player_input == KEY_LEFT)
	{
		i = 0;
		while ((size_t)i < sess->board_size)
		{
			if (sess->board[i] != 0)
			{
				col = i / sess->board_width;
				row = i % sess->board_width;

				j = i;
				//j -= sess->board_width;
				j -= (i - (int)sess->board_width < 0) ? 0 : sess->board_width;
				while (sess->board[j] == 0 && (size_t)j > row)
					j -= sess->board_width;

				//j = row; // +3
				while (j / sess->board_width < col) // > row
				{
					mod = j / sess->board_width;
					if (sess->board[i + (mod * sess->board_width - col * sess->board_width)] == 0)
					{
						sess->board[i + (mod * sess->board_width - col * sess->board_width)] = sess->board[i];
						sess->board[i] = 0;
						test = 1;
						break ;
					}
					else if (sess->board[i + (mod * sess->board_width - col * sess->board_width)] == sess->board[i])
					{
						test = 1;
						if (locked_indexes[i + (mod * sess->board_width - col * sess->board_width)])
						{
							sess->board[i + ((mod + 1) * sess->board_width - col * sess->board_width)] = sess->board[i];
							sess->board[i] = 0;
							break;
						}
						locked_indexes[i + (mod * sess->board_width - col * sess->board_width)] = 1;
						sess->board[i + (mod * sess->board_width - col * sess->board_width)] *= 2;
						sess->board[i] = 0;
						if (sess->board[i + (mod - row)] == WIN_VALUE)
							player_win(p_win);
						break ;
					}
					j += sess->board_width; // j--
				}
			}
			i++;
		}
	}
	else if (sess->player_input == KEY_RIGHT)
	{
		i = sess->board_size - 1;
		while (i >= 0)
		{
			if (sess->board[i] != 0)
			{
				col = i / sess->board_width;
				row = i % sess->board_width;

				j = i;
				j += (i + sess->board_width > sess->board_size) ? 0 : sess->board_width;
				while (sess->board[j] == 0 && (size_t)j < row + 3 * sess->board_width)
					j += sess->board_width;

				//j = row + 3 * sess->board_width; // +3
				while (j < 16 && j / sess->board_width > col) // > row
				{
					mod = j / sess->board_width;
					int shift = i + mod * sess->board_width - col * sess->board_width;
					if (sess->board[shift] == 0)
					{
						sess->board[shift] = sess->board[i];
						sess->board[i] = 0;
						test = 1;
						break ;
					}
					else if (sess->board[shift] == sess->board[i])
					{
						test = 1;
						if (locked_indexes[shift])
						{
							sess->board[shift + sess->board_width] = sess->board[i];
							sess->board[i] = 0;
							break;
						}
						locked_indexes[i + (mod * sess->board_width - col * sess->board_width)] = 1;
						sess->board[i + (mod * sess->board_width - col * sess->board_width)] *= 2;
						sess->board[i] = 0;
						if (sess->board[i + (mod - row)] == WIN_VALUE)
							player_win(p_win);
						break ;
					}
					j -= sess->board_width; // j--
				}
			}
			i--;
		}

	}
	else if (sess->player_input == 96)
	{
		fill_random_tile(sess, time(NULL));
	}

	if (test && !fill_random_tile(sess, time(NULL)))
	{
		if (!possible_move(sess))
		{
			(*p_win)->caption = ft_strdup("Sorry, you lost the game !");
			(*p_win)->caption2 = ft_strdup("");
			refresh_window(*p_win);
		}
	}
}
