/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 19:07:20 by gdruel            #+#    #+#             */
/*   Updated: 2014/11/14 13:59:23 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char	*s;
	size_t	i;

	i = 0;
	s = (char *)malloc((sizeof(char) * (size + 1)));
	if (s)
	{
		while (i != size + 1)
		{
			s[i] = 0;
			i++;
		}
		return (s);
	}
	return (NULL);
}
