/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:35:43 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/03 10:08:31 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

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
