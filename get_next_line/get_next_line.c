/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 12:28:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/03 19:05:09 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "get_next_line.h"

// 8 lignes
static t_list		*new_parser(int fd)
{
	t_parser	parser;

	parser.fd = fd;
	parser.bcount = 0;
	parser.buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
	if (!parser.buffer)
		return (NULL);
	return (ft_lstnew((void *)&parser, sizeof(parser)));
}

// 15 lignes
static t_parser		*get_fd_parser(t_list *parser_list, int fd)
{
	t_parser	*parser;

	parser = (t_parser *)parser_list->content;
	//ft_putnbr(parser->bcount);
	while (parser->fd != fd)
	{
		if (!parser_list->next)
		{
			parser_list->next = new_parser(fd);
			parser = (t_parser *)parser_list->next->content;
			break ;
		}
		parser_list = parser_list->next;
		parser = (t_parser *)parser_list->content;
	}
	return (parser);
}

// 6 lignes
static void		clear(void *elem, size_t size)
{
	(void)		size;
	t_parser	*parser;

	parser = (t_parser *)elem;
	ft_memdel((void **)&parser->buffer);
	ft_memdel(&elem);
}

// 38 lignes
static size_t	get_line(t_parser *parser, t_list **strings)
{
	char	*eol;
	size_t	total_bcount;
	t_list	*lst;
	size_t	truncated_bytes;

	lst = NULL;
	eol = NULL;
	total_bcount = 0;
	while (!eol)
	{
		if (parser->bcount == 0)
			parser->bcount = read(parser->fd, parser->buffer, BUFF_SIZE);
		if (parser->bcount == 0)
			return (0);
		total_bcount += parser->bcount;
		if (!*strings)
			*strings = ft_lstnew(NULL, 0);
		if (!lst)
			lst = *strings;
		(*strings)->content = (char *)malloc(sizeof(char) * parser->bcount);
		// TODO
		//if (!lst->content)
		//	return (-1);

		eol = ft_memccpy((*strings)->content, (void *)parser->buffer, '\n', parser->bcount);
		if (eol)
		{
			truncated_bytes = (int)eol - (int)(*strings)->content;
			((char *)(*strings)->content)[truncated_bytes - 1] = '\0';
			(*strings)->content_size = truncated_bytes - 1;
			parser->buffer = ft_memmove((void *)parser->buffer, (void *)&(parser->buffer[truncated_bytes]), BUFF_SIZE - truncated_bytes);
			parser->bcount -= truncated_bytes;
			break;
		}
		(*strings)->content_size = parser->bcount;
		((char *)(*strings)->content)[parser->bcount] = '\0';
		parser->bcount = 0;
		(*strings)->next = ft_lstnew(NULL, 0);
		*strings = (*strings)->next;
	}
	*strings = lst;
	return (total_bcount);
}

// 30 lignes
int		get_next_line(const int fd, char **line)
{
	static t_list	*s_parsers = NULL;
	t_parser		*parser;
	t_list			*strings;
	t_list			*strn;
	size_t			line_length;
	t_list			*last;
	t_list			*start;

	parser = NULL;
	strings = NULL;
	if (!s_parsers && !(s_parsers = new_parser(fd)))
		return (-1);
	parser = get_fd_parser(s_parsers, fd);
	line_length = get_line(parser, &strings);
	//if (line_length < 0)
	//	return (-1);
	if (line_length == 0)
	{
		/*
		** Remove an element from the list
		*/
		start = s_parsers;
		last = NULL;
		while (((t_parser *)s_parsers->content)->fd != fd)
		{
			last = s_parsers;
			s_parsers = s_parsers->next;
			if (!s_parsers)
				return (-1);
		}
		if (last && s_parsers->next && last->next)
			last->next = s_parsers->next;
		if (s_parsers == start)
			start = start->next;
		ft_lstdelone(&s_parsers, &clear);
		s_parsers = start;
		return (0);
	}
	if (*line)
		ft_memdel ((void *)line);
	*line = (char *)malloc(sizeof(char) * line_length);
	if (!*line)
		return (-1);
	*line[0] = '\0';
	while (strings)
	{
		strn = strings;
		ft_strncat(*line, (char *)strings->content, strings->content_size);
		strings = strings->next;
		free(strn);
	}
	return (1);
}
