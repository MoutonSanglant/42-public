/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/01/02 12:28:41 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/07 17:38:55 by tdefresn         ###   ########.fr       */
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
	ft_putendl("malloc: parser.buffer");
	parser.buffer = (char *)ft_memalloc(sizeof(char) * BUFF_SIZE + 1);
	if (!parser.buffer)
		return (NULL);
	ft_putendl("malloc: parser");
	ft_putendl("malloc: parser.content");
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
				break;
		}
		//parser->buffer[parser->bcount] = '\0';
		total_bcount += parser->bcount;
		if (!*strings)
		{
			ft_putendl("malloc: strings");
			*strings = ft_lstnew(NULL, 0);

		}
		if (!lst)
			lst = *strings;
		ft_putendl("malloc: strings.content");
		(*strings)->content = (char *)ft_memalloc(sizeof(char) * (parser->bcount + 1));
		(*strings)->content_size = parser->bcount;
		if (!(*strings)->content)
		{
			ft_putendl("LEAKING\n\nHERE");
			return (0);
		}

		eol = ft_memccpy((*strings)->content, (void *)parser->buffer, '\n', parser->bcount);
		if (eol)
		{
			truncated_bytes = (int)eol - (int)(*strings)->content;
			((char *)(*strings)->content)[truncated_bytes - 1] = '\0';
			parser->bcount -= truncated_bytes;
			parser->buffer = (char *)ft_memmove((void *)parser->buffer, (void *)&(parser->buffer[truncated_bytes]), parser->bcount);
			break;
		}
		parser->bcount = 0;
		ft_putendl("malloc: strings.next");
		if ((*strings)->next)
		{
			ft_putendl("FREE\n\nLEAK");
			*strings = lst;
			return (0);
		}
		(*strings)->next = ft_lstnew(NULL, 0);
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
	if ((line_length = get_line(parser, &strings)))
	{
		if (*line)
		{
			ft_putendl("memdel: line");
			ft_memdel ((void *)line);
		}
		ft_putendl("malloc: line");
		*line = (char *)ft_memalloc(sizeof(char) * line_length + 1);
		if (!*line)
			return (-1);
		//*line[0] = '\0';
		while (strings)
		{
			tmp_lst = strings;
			//ft_strncat(*line, (char *)strings->content, strings->content_size);
			ft_strcat(*line, (char *)strings->content);
			strings = strings->next;
			ft_putendl("memdel: strings->content");
			ft_memdel ((void **)&tmp_lst->content);
			ft_putendl("memdel: strings");
			ft_memdel ((void **)&tmp_lst);
		}
		//(void) last;
		//free(s_parsers);
		//s_parsers = NULL;
	}
	else
	{
		/*
		** Remove an element from the list
		*/
		while (strings)
		{
			ft_putendl("LEAKING\n\n\nSTRING");
			tmp_lst = strings;
			//ft_strncat(*line, (char *)strings->content, strings->content_size);
			//ft_strcat(*line, (char *)strings->content);
			strings = strings->next;
			ft_putendl("memdel: strings->content");
			ft_memdel ((void **)&tmp_lst->content);
			ft_putendl("memdel: strings");
			ft_memdel ((void **)&tmp_lst);
		}
		//free(s_parsers);
		//s_parsers = NULL;
		t_list *toto;
		last = NULL;
		tmp_lst = s_parsers;
		while (((t_parser *)tmp_lst->content)->fd != fd)
		{
			last = tmp_lst;
			ft_putendl("TMP_LST CHANGED");
			tmp_lst = tmp_lst->next;
			if (!tmp_lst)
				return (-1);
		}
		if (last && tmp_lst->next && last->next)
			last->next = tmp_lst->next;
		toto = s_parsers;
		if (tmp_lst == s_parsers)
			s_parsers = s_parsers->next;
		ft_putendl("memdel: s_parsers.content.buffer");
		ft_memdel((void **)&((t_parser *)tmp_lst->content)->buffer);
		ft_putendl("memdel: s_parsers.content");
		ft_memdel((void **)&tmp_lst->content);
		ft_putendl("memdel: s_parsers");
		ft_memdel((void **)&tmp_lst);
		if (!s_parsers && !tmp_lst)
			ft_putendl("FULLY\n\n\nFLUSHED");
		return (0);
	}
	return (1);
}
