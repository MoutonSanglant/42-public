/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:35:40 by tdefresn          #+#    #+#             */
/*   Updated: 2016/01/26 22:18:00 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		i;

	if (!s || !f)
	{
		ft_putendl("ft_strmapi returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	new_str = ft_strnew(ft_strlen(s));
	if (new_str)
	{
		i = 0;
		while (s[i] != '\0')
		{
			new_str[i] = f(i, s[i]);
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}

#else

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*new_str;
	int		i;

	new_str = ft_strnew(ft_strlen(s));
	if (new_str)
	{
		i = 0;
		while (s[i] != '\0')
		{
			new_str[i] = f(i, s[i]);
			i++;
		}
		new_str[i] = '\0';
	}
	return (new_str);
}
#endif
