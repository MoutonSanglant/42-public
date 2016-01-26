/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:28 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:32:50 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG

# include "libft.h"

void	ft_strclr(char *s)
{
	if (!s)
	{
		ft_putendl("ft_strclr returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return ;
	}
	while (*s != '\0')
		*s++ = '\0';
}

#else

void	ft_strclr(char *s)
{
	while (*s != '\0')
		*s++ = '\0';
}
#endif
