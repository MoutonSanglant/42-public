/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:17 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/03 16:16:08 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	char	*str_new;
	size_t	i;

	str_new = ft_strnew(len);
	if (str_new)
	{
		i = 0;
		while (i < len)
		{
			str_new[i] = s[start + i];
			i++;
		}
		str_new[i] = '\0';
	}
	return (str_new);
}
