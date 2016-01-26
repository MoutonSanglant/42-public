/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:35:43 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:18:52 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

char	*ft_strncat(char *s1, char const *s2, size_t n)
{
	size_t	i;
	char	*ptr;

	if (!s1 || !s2)
	{
		ft_putendl("ft_strncat returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	ptr = s1;
	while (*ptr++)
		;
	ptr--;
	i = 0;
	while (i < n)
	{
		ptr[i] = s2[i];
		i++;
	}
	ptr[i] = '\0';
	return (s1);
}

#else

char	*ft_strncat(char *s1, char const *s2, size_t n)
{
	size_t	i;
	char	*ptr;

	ptr = s1;
	while (*ptr++)
		;
	ptr--;
	i = 0;
	while (i < n)
	{
		ptr[i] = s2[i];
		i++;
	}
	ptr[i] = '\0';
	return (s1);
}
#endif
