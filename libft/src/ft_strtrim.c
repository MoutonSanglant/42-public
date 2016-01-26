/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:09 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 19:18:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

char	*ft_strtrim(char const *s)
{
	size_t		start;
	size_t		end;
	size_t		i;

	if (!s)
	{
		ft_putendl("ft_strtrim error: sent parameter is NULL");
		return (NULL);
	}
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

#else

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
#endif
