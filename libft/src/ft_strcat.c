/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:33 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:32:43 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifdef DEBUG

# include "libft.h"

char	*ft_strcat(char *s1, char const *s2)
{
	char	*ptr;

	if (!s1 || !s2)
	{
		ft_putendl("ft_strcat returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	ptr = s1;
	while (*ptr++)
		;
	ptr--;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (s1);
}

#else

char	*ft_strcat(char *s1, char const *s2)
{
	char	*ptr;

	ptr = s1;
	while (*ptr++)
		;
	ptr--;
	while (*s2)
		*ptr++ = *s2++;
	*ptr = '\0';
	return (s1);
}
#endif
