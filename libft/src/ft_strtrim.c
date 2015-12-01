/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:09 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/01 14:31:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim(char const *s)
{
	size_t		start;
	size_t		end;
	size_t		i;

	start = 0;
	end = 0;
	i = 0;
	while (s[i] != '\0')
	{
		if (!ft_isspace(s[i]))
		{
			if (start == 0)
				start = i;
			end = i;
		}
		i++;
	}
	return (ft_strsub(s, start, ((end + 1) - start)));
}
