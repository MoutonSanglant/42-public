/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 19:19:44 by gdruel            #+#    #+#             */
/*   Updated: 2014/11/14 20:11:19 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*t;
	unsigned int	i;
	size_t			len;

	i = 0;
	len = ft_strlen(s);
	t = ft_strnew(len);
	while (i < len)
	{
		t[i] = f(i, s[i]);
		i++;
	}
	return (t);
}
