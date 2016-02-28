/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/07 18:05:00 by gdruel            #+#    #+#             */
/*   Updated: 2014/11/14 20:11:00 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*t;
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(s);
	t = ft_strnew(len);
	while (i < len)
	{
		t[i] = f(s[i]);
		i++;
	}
	return (t);
}
