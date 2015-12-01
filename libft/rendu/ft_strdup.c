/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:13 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/01 12:34:14 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strdup(char const *s)
{
	char	*str_new;
	char	*ptr;

	str_new = (char *)malloc(sizeof(char) * ft_strlen(s));
	if (str_new)
	{
		ptr = str_new;
		while (*s)
			*ptr++ = *s++;
		*ptr = *s;
	}
	return (str_new);
}
