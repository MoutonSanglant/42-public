/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/28 19:25:18 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/02 03:43:18 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

#include "get_next_line.h"

#define DEBUG 0

static t_file_pointer	*get_file_pointer(t_list *file_list, int fd)
{
	t_file_pointer	*fp;

	fp = (t_file_pointer *) file_list->content;
	while (fp->fd != fd)
	{
		if (file_list->next == NULL)
		{
			fp = (t_file_pointer *)malloc(sizeof(t_file_pointer));
			if (!fp)
				return (NULL);
			fp->fd = fd;
			fp->bytes = 0;
			fp->buffer = NULL;
			//fp->buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
			//file_list->next = ft_lstnew((void *) fp, sizeof(fp));
			file_list->next = (t_list *)malloc(sizeof(t_list));
			file_list->next->content = (void *) fp;
			file_list->next->content_size = sizeof(fp);
			file_list->next->next = NULL;
			break;
		}
		file_list = file_list->next;
		fp = (t_file_pointer *) file_list->content;
	}
	return (fp);
}

/*
** return value
** 1:	line has been succesfully read
** 0:	read is done
** -1:	an error occured
*/
int		get_next_line(int const fd, char **line)
{
	static t_list	*s_files = NULL;
	t_file_pointer	*file_pointer;
	t_list			*list;
	t_list			*root_list;
	int				line_size;
	size_t			i;

#if DEBUG > 0
	ft_putendl("== get next line ==");
#endif
	list = NULL;
	line_size = 0;
	file_pointer = NULL;
	if (!s_files)
	{
		//ft_putendl("!!!!!!!!!!!!!!!!");
		file_pointer = (t_file_pointer *)malloc(sizeof(t_file_pointer));
		if (!file_pointer)
			return (-1);
		file_pointer->fd = fd;
		file_pointer->bytes = 0;
		file_pointer->buffer = NULL;
		//file_pointer->buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
		//s_files = ft_lstnew((void *) file_pointer, sizeof(file_pointer));
		s_files = (t_list *)malloc(sizeof(t_list));
		s_files->content = (void *)file_pointer;
		s_files->content_size = sizeof(file_pointer);
		s_files->next = NULL;
		if (!s_files)
			return (-1);
	}
	else
	{
		//ft_putendl("!!!!!!!!!!!!!!!!");
		file_pointer = get_file_pointer(s_files, fd);
	}
	if (!file_pointer)
		return (-1);
	//if (!file_pointer->buffer)
	//		return (-1);
	
	if (!file_pointer->buffer)
	{
		//ft_putendl("@@@@@@@@@@@");
		file_pointer->buffer = (char *)malloc(sizeof(char) * BUFF_SIZE);
		if (!file_pointer->buffer)
			return (-1);
#if DEBUG > 0
		ft_putendl("Buffer allocated");
#endif
		file_pointer->bytes = read(fd, file_pointer->buffer, BUFF_SIZE);
	}

	//if (file_pointer->bytes == 0)
	//	file_pointer->bytes = read(fd, file_pointer->buffer, BUFF_SIZE);

	//if (file_pointer->bytes != 0)
	//if (!file_pointer->buffer)
	//	return (-1);
	else
	{
		//ft_putendl(";;;;;;;;;;");
#if DEBUG > 0
		ft_putendl("Buffer already allocated");
#endif
			
		while (file_pointer->bytes > 0 && file_pointer->buffer[0] != '\n')
		{
			file_pointer->buffer++;
			file_pointer->bytes--;
		}
		file_pointer->buffer++;
		file_pointer->bytes--;
		
		
		//list = ft_lstnew((void const *) file_pointer->buffer, file_pointer->bytes);
		//root_list = list;
	}
	
	if (file_pointer->buffer[0] == '\n')
	{
#if DEBUG > 0
		ft_putstr("malloc empty line");
#endif
		*line = (char *)malloc(sizeof(char));
		*line[0] = '\0';
#if DEBUG > 0
		ft_putendl(": ok");
#endif
		return (1);
	}
	i = 0;
	while (file_pointer->buffer[i] != '\n')
	{
		i = 0;
		line_size += file_pointer->bytes;
#if DEBUG > 0
		ft_putnbr(file_pointer->bytes);
		ft_putstr(" bytes read (total: ");
		ft_putnbr(line_size);
		ft_putendl(")");
#endif
		if (file_pointer->bytes == 0)
			return (0);

		while (i < file_pointer->bytes)
		{
			if (file_pointer->buffer[i] == '\n')
			{
#if DEBUG > 0
				ft_putendl("end of line");
#endif
				//line_size -= (bcount - i);
				break;
			}
			i++;
		}
		if (!list)
		{
#if DEBUG > 0
			ft_putstr("new list");
#endif
			if (i == file_pointer->bytes)
				list = ft_lstnew((void const *) file_pointer->buffer, file_pointer->bytes);
			else
				list = ft_lstnew((void const *) file_pointer->buffer, i);
			root_list = list;
			if (!list)
				return (-1);
#if DEBUG > 0
			ft_putendl(": ok");
#endif
		}
		else
		{
#if DEBUG > 0
			ft_putstr("new list elem");
#endif
			root_list = list;
			while (list->next)
				list = list->next;
			/*
			** need to use ft_strccpy to cpy until \n
			*/
			if (i == file_pointer->bytes)
				list->next = ft_lstnew((void const *) file_pointer->buffer, file_pointer->bytes);
			else	
				list->next = ft_lstnew((void const *) file_pointer->buffer, i);
			if (!list->next)
				return (-1);
#if DEBUG > 0
			ft_putendl(": ok");
#endif
		}
		if (i !=file_pointer->bytes)
			break;
		file_pointer->bytes = read(fd, file_pointer->buffer, BUFF_SIZE);
	}
	//while (*file_pointer->buffer++ != '\n')
	//	;
	//	file_pointer->buffer++;
	list = root_list;
	/*if (*line)
	{
		ft_putstr("free line");
		free(*line);
		ft_putendl(": ok");
	}*/
#if DEBUG > 0
	ft_putstr("malloc line");
#endif
	*line = (char *)malloc(sizeof(char) * line_size);
#if DEBUG > 0
	ft_putendl(": ok");
#endif
	while (list)
	{
#if DEBUG > 0
		ft_putstr("fill line ");
#endif
		//ft_putnbr(list->content_size);
		//ft_putendl((char *)list->content_size);
		ft_strncat(*line, (char *)list->content, list->content_size);
		list = list->next;
#if DEBUG > 0
		ft_putendl(": ok");
#endif
	}
	return (1);
}
