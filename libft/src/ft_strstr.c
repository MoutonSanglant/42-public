/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:14 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/03 10:35:04 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strstr(char const *s1, char const *s2)
{
	char const	*ptr_s1;
	char const	*ptr_s2;

	while (*s1)
	{
		ptr_s1 = s1;
		ptr_s2 = s2;
		while (*ptr_s2 == *ptr_s1)
		{
			ptr_s1++;
			ptr_s2++;
		}
		if (!*ptr_s2)
			return ((char *)s1);
		s1++;
	}
	return (NULL);
}
