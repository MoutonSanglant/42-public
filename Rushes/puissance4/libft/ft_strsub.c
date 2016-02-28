/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 19:27:32 by gdruel            #+#    #+#             */
/*   Updated: 2014/11/14 14:07:59 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char			*t;
	unsigned int	i;

	i = 0;
	t = ft_strnew(len);
	if (!s || !t)
		return (NULL);
	while (i < (unsigned int)len)
	{
		t[i] = s[start + i];
		i++;
	}
	return (t);
}
