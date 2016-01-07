/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 12:28:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/06 18:33:56 by tdefresn         ###   ########.fr       */
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
	parser.buffer = (char *)malloc(sizeof(char) * BUFF_SIZE + 1);
	if (!parser.buffer)
		return (NULL);
	return (ft_lstnew((void *)&parser, sizeof(parser)));
}

// 15 lignes
static t_parser		*get_fd_parser(t_list *parser_list, int fd)
{
	t_parser	*parser;

	parser = (t_parser *)parser_list->content;
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
#include <string.h>
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
		{
			parser->bcount = read(parser->fd, parser->buffer, BUFF_SIZE);
			if (parser->bcount == 0)
			{
				//parser->bcount = total_bcount;
				*strings = lst;
				return (total_bcount);
			}
		}
		//parser->buffer[parser->bcount] = '\0';
		total_bcount += parser->bcount;
		if (!*strings)
			*strings = ft_lstnew(NULL, 0);
		if (!lst)
			lst = *strings;
		(*strings)->content = (char *)ft_memalloc(sizeof(char) * parser->bcount + 1);
		(*strings)->content_size = parser->bcount;
		if (!(*strings)->content)
			return (0);

		eol = ft_memccpy((*strings)->content, (void *)parser->buffer, '\n', parser->bcount);
		if (eol)
		{
			truncated_bytes = (int)eol - (int)(*strings)->content;
			parser->bcount -= truncated_bytes;
			parser->buffer = (char *)ft_memmove((void *)parser->buffer, (void *)&(parser->buffer[truncated_bytes]), parser->bcount);
			break;
		}
		parser->bcount = 0;
		(*strings)->next = ft_lstnew(NULL, 0);
		if (!(*strings)->next)
			return (0);
		*strings = (*strings)->next;
		(*strings)->next = NULL;
		(*strings)->content = NULL;
		(*strings)->content_size = 0;
	}
	*strings = lst;
	return (total_bcount);
}

// 30 lignes
int		get_next_line(const int fd, char **line)
{
	static t_list	*s_parsers = NULL;
	t_parser		*parser; // optional
	t_list			*strings;
	t_list			*tmp_lst;
	t_list			*last;
	size_t			line_length;

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
		last = NULL;
		tmp_lst = s_parsers;
		while (((t_parser *)tmp_lst->content)->fd != fd)
		{
			last = tmp_lst;
			tmp_lst = tmp_lst->next;
			if (!tmp_lst)
				return (-1);
		}
		if (last && tmp_lst->next && last->next)
			last->next = tmp_lst->next;
		if (tmp_lst == s_parsers)
			s_parsers = s_parsers->next;
		ft_lstdelone(&tmp_lst, &clear);
		return (0);
	}
	if (*line)
		ft_memdel ((void *)line);
	*line = (char *)malloc(sizeof(char) * line_length + 1);
	if (!*line)
		return (-1);
	*line[0] = '\0';
	while (strings)
	{
		tmp_lst = strings;
		ft_strncat(*line, (char *)strings->content, strings->content_size);
		strings = strings->next;
		ft_memdel ((void **)&tmp_lst->content);
		ft_memdel ((void **)&tmp_lst);
	}
	return (1);
}
