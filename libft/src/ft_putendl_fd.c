/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:02 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 20:16:13 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_putendl_fd(char const *s, int fd)
{
	if (!s)
	{
		ft_putendl("ft_putendl_fd returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}

#else

void	ft_putendl_fd(char const *s, int fd)
{
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
#endif
