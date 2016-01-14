/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/13 14:44:53 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/14 14:39:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		if (!fd_list)
			return (-1);
	}
	if (prev)
	{
		if (fd_list->next)
			prev->next = fd_list->next;
		else
			prev->next = NULL;
		*parser_list = prev;
	}
	if (fd_list == *parser_list)
		*parser_list = (*parser_list)->next;
	ft_memdel((void **)&((t_parser *)fd_list->content)->buf);
	ft_memdel((void **)&fd_list->content);
	ft_memdel((void **)&fd_list);
	return (0);
}

static t_parser	*get_fd_parser(t_list **s_parsers, t_list *parser_list, int fd)
{
	t_parser	p;

	p.fd = fd;
	p.bs = 0;
	if (!*s_parsers && (!(p.buf = (char *)ft_memalloc(BUFF_SIZE + 1))
		|| !(*s_parsers = ft_lstnew((void *)&p, sizeof(p)))))
	{
		if (p.buf)
			ft_memdel((void **)&p.buf);
		return (NULL);
	}
	parser_list = *s_parsers;
	while (((t_parser *)parser_list->content)->fd != fd)
	{
		if (!parser_list->next
				&& (!(p.buf = (char *)ft_memalloc((BUFF_SIZE + 1)))
				|| !(parser_list->next = ft_lstnew((void *)&p, sizeof(p)))))
		{
			if (p.buf)
				ft_memdel((void **)&p.buf);
			return (NULL);
		}
		parser_list = parser_list->next;
	}
	return ((t_parser *)parser_list->content);
}

static int		read_until_eol(t_list **s, t_parser *p, size_t *total_bcount)
{
	size_t	eol;

	if (p->bs == 0 && (!(p->bs = read(p->fd, p->buf, BUFF_SIZE)) || p->bs <= 0))
		return (1 + (2 * p->bs));
	*total_bcount += (size_t)p->bs;
	if (!*s)
		*s = ft_lstnew(NULL, 0);
	else
		*s = (*s)->next;
	(*s)->content = (char *)ft_memalloc(p->bs + 1);
	if (!(*s)->content)
		return (-1);
	(*s)->content_size = (size_t)p->bs;
	if ((eol = (size_t)ft_memccpy((*s)->content, (void *)p->buf,
									'\n', (size_t)p->bs)))
	{
		eol -= (size_t)(*s)->content;
		p->bs -= (long)eol;
		((char *)(*s)->content)[eol - 1] = '\0';
		p->buf = (char *)ft_memmove((void *)p->buf,
							(void *)&(p->buf[eol]), (long)p->bs);
		return (1);
	}
	p->bs = 0;
	return (0);
}

static int		get_fd_line(char **line, t_list **s_parsers,
							int fd, t_list **strings)
{
	t_list		*first;
	t_parser	*parser;
	size_t		total_bcount;
	int			r;

	r = 0;
	total_bcount = 0;
	first = NULL;
	if (!(parser = get_fd_parser(s_parsers, *s_parsers, fd)))
		return (-1);
	while (!r)
	{
		if ((r = read_until_eol(strings, parser, &total_bcount)) && r < 0)
		{
			clear_fd_parser(s_parsers, fd);
			return (-1);
		}
		if (!first && *strings)
			first = *strings;
		if (r == 0)
			(*strings)->next = ft_lstnew(NULL, 0);
	}
	*strings = first;
	if (!(*line = (char *)ft_memalloc(total_bcount + 1)))
		return (-1);
	r = (total_bcount > 0) ? 1 : 0;
	return (r);
}

int				get_next_line(const int fd, char **line)
{
	static t_list	*s_parsers = NULL;
	t_list			*strings;
	t_list			*prev_str;
	int				r;

	if (fd < 0 || !line)
		return (-1);
	strings = NULL;
	if ((r = get_fd_line(line, &s_parsers, fd, &strings)))
	{
		while (strings)
		{
			prev_str = strings;
			if (strings->content)
			{
				ft_strcat(*line, (char *)strings->content);
				ft_memdel((void **)&prev_str->content);
			}
			strings = strings->next;
			ft_memdel((void **)&prev_str);
		}
	}
	else
	{
		r = clear_fd_parser(&s_parsers, fd);
		*line[0] = '\0';
	}
	return (r);
}
