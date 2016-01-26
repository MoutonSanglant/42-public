/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:22 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:32:59 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG

# include "libft.h"

char	*ft_strcpy(char *dst, char const *src)
{
	char *ptr;

	if (!dst | !src)
	{
		ft_putendl("ft_strcpy returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	ptr = dst;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dst);
}

#else

char	*ft_strcpy(char *dst, char const *src)
{
	char *ptr;

	ptr = dst;
	while (*src)
		*ptr++ = *src++;
	*ptr = '\0';
	return (dst);
}
#endif
