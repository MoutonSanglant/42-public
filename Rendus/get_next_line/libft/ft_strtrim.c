/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:09 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/14 11:51:54 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	size_t		start;
	size_t		end;
	size_t		i;

	start = (size_t)-1;
	end = 0;
	i = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
		{
			if (start == (size_t)-1)
				start = i;
			end = i;
		}
		i++;
	}
	if (start == (size_t)-1)
		return (ft_strdup(""));
	return (ft_strsub(s, start, ((end + 1) - start)));
}
