/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 12:28:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/08 06:46:25 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "get_next_line.h"

static int		clear_fd_parser(t_list **parser_list, int fd)
{
	t_list	*fd_list;
	t_list	*prev;

	prev = NULL;
	fd_list = *parser_list;
	while (((t_parser *)fd_list->content)->fd != fd)
	{
		prev = fd_list;
		fd_list = fd_list->next;
		// ??
		if (!fd_list)
			return (-1);
	}
	if (prev && fd_list->next && prev->next)
		prev->next = fd_list->next;
	if (fd_list == (*parser_list))
		*parser_list = (*parser_list)->next;
	ft_memdel((void **)&((t_parser *)fd_list->content)->buffer);
	ft_memdel((void **)&fd_list->content);
	ft_memdel((void **)&fd_list);
	return (0);
}

static t_parser	*get_fd_parser(t_list **s_parsers, int fd)
{
	t_list		*parser_list;
	t_parser	p;

	p.fd = fd;
	p.bcount = 0;
	if (!*s_parsers && (!(p.buffer = (char *)ft_memalloc(BUFF_SIZE + 1))
		|| !(*s_parsers = ft_lstnew((void *)&p, sizeof(p)))))
	{
		if (p.buffer)
			ft_memdel((void **)&p.buffer);
		return (NULL);
	}
	parser_list = *s_parsers;
	while (((t_parser *)parser_list->content)->fd != fd)
	{
		if (!parser_list->next
				&& (!(p.buffer = (char *)ft_memalloc((BUFF_SIZE + 1)))
				|| !(parser_list->next = ft_lstnew((void *)&p, sizeof(p)))))
		{
			if (p.buffer)
				ft_memdel((void **)&p.buffer);
			return (NULL);
		}
		parser_list = parser_list->next;
	}
	return ((t_parser *)parser_list->content);
}

static int	to_eol(t_list **s, t_parser *p, size_t *total_bcount)
{
	size_t	eol;

	if (p->bcount == 0
		&& (!(p->bcount = read(p->fd, p->buffer, BUFF_SIZE))))
		return (1);
	*total_bcount += p->bcount;
	if (!*s)
		*s = ft_lstnew(NULL, 0);
	else
		*s = (*s)->next;
	(*s)->content = (char *)ft_memalloc(p->bcount + 1);
	if (!(*s)->content)
		return (-1);
	(*s)->content_size = p->bcount;
	if ((eol = (size_t)ft_memccpy((*s)->content,
									(void *)p->buffer, '\n', p->bcount)))
	{
		eol -= (size_t)(*s)->content;
		p->bcount -= eol;
		((char *)(*s)->content)[eol - 1] = '\0';
		p->buffer = (char *)ft_memmove((void *)p->buffer,
										(void *)&(p->buffer[eol]), p->bcount);
		return (1);
	}
	p->bcount = 0;
	return (0);
}

static int	get_fd_line(char **line, t_list **s_parsers, int fd, t_list **strings)
{
	t_list		*first;
	t_parser	*parser;
	size_t		total_bcount;
	int			r;

	r = 0;
	total_bcount = 0;
	first = NULL;
	if (!(parser = get_fd_parser(s_parsers, fd)))
		return (-1);
	while (!r)
	{
		if ((r = to_eol(strings, parser, &total_bcount)) && r < 0)
			return (-1);
		if (!first && *strings)
			first = *strings;
		if (r == 0)
			(*strings)->next = ft_lstnew(NULL, 0);
	}
	*strings = first;
	if (*line)
		ft_memdel ((void **)&(*line));
	if (!(*line = (char *)ft_memalloc(total_bcount + 1)))
		return (-1);
	return (total_bcount);
}

int		get_next_line(const int fd, char **line)
{
	static t_list	*s_parsers = NULL;
	t_list			*strings;
	t_list			*prev_str;
	int				r;

	r = 0;
	strings = NULL;
	if ((r = get_fd_line(line, &s_parsers, fd, &strings)))
	{
		while (strings)
		{
			ft_strcat(*line, (char *)strings->content);
			prev_str = strings;
			strings = strings->next;
			ft_memdel ((void **)&prev_str->content);
			ft_memdel ((void **)&prev_str);
		}
	}
	else
		r = clear_fd_parser(&s_parsers, fd);
	return (r);
}
