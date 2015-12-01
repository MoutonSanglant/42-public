/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:14 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/01 12:36:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strstr(char const *haystack, char const *needle)
{
	char const	*ptr;
	char const	*ptr_haystack;

	while (*haystack)
	{
		ptr = needle;
		ptr_haystack = haystack;
		while (*ptr == *ptr_haystack)
		{
			ptr++;
			ptr_haystack++;
		}
		if (!*ptr)
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}
