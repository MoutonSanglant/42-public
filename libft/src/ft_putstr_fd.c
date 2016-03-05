/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:40 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/05 23:49:10 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

void	ft_putstr_fd(char const *s, int fd)
{
	if (!s)
	{
		ERROR_PARAM("ft_putstr_fd");
		return ;
	}
	write(fd, s, ft_strlen(s));
}

#else

void	ft_putstr_fd(char const *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
#endif
