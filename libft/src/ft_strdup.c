/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:13 by tdefresn          #+#    #+#             */
<<<<<<< HEAD
<<<<<<< HEAD
/*   Updated: 2016/04/09 18:49:13 by tdefresn         ###   ########.fr       */
=======
/*   Updated: 2015/12/14 11:51:53 by tdefresn         ###   ########.fr       */
>>>>>>> a3b3e17... libft retry
=======
/*   Updated: 2016/01/26 22:08:36 by tdefresn         ###   ########.fr       */
>>>>>>> ee0a2bb... libft: fin du debat.
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

char	*ft_strdup(char const *s1)
{
	char	*str_new;
	char	*ptr;

	if (!s1)
	{
		ft_putendl("ft_strdup returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	str_new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str_new)
	{
		ptr = str_new;
		while (*s1)
			*ptr++ = *s1++;
		*ptr = *s1;
	}
	return (str_new);
}

#else

char	*ft_strdup(char const *s1)
{
	char	*str_new;
	char	*ptr;

	str_new = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str_new)
	{
		ptr = str_new;
		while (*s1)
			*ptr++ = *s1++;
		*ptr = *s1;
	}
	return (str_new);
}
#endif
