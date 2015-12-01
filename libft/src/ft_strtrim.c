/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:34:09 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/01 12:51:24 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

char	*ft_strtrim(char const *s)
{
	char const	*s_firstchar;
	char		*str_new;
	int			last_char;
	size_t		len;
	size_t		i;

	s_firstchar = NULL;
	last_char = 0;
	len = 0;
	while (*s != '\0')
	{
		if (*s != ' ' && *s != '\n' && *s != '\t')
		{
			if (s_firstchar == NULL)
				s_firstchar = s;
			last_char = (int)s;
			len = 1;
		}
		s++;
	}
	len += last_char - ((int)s_firstchar);
	str_new = ft_strnew(sizeof(char) * len);
	if (str_new)
	{
		s = s_firstchar;
		i = 0;
		while (i < len)
		{
			str_new[i] = *s++;
			i++;
		}
		str_new[i] = '\0';
	}
	return (str_new);
}
