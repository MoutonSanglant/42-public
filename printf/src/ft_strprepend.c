/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprepend.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/02/23 12:19:51 by tdefresn          #+#    #+#             */
/*   Updated: 2016/02/23 12:32:15 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#ifdef DEBUG

static void		prepend(char **str, char *prefix)
{
	char	*str_new;

	str_new = ft_strjoin(prefix, *str);
	ft_strdel(str);
	*str = str_new;
}

void			ft_strprepend(char **str, char *prefix)
{
	if (!str || !(*str) || !prefix)
	{
		ft_putendl("ft_strprepend returned the following error:\n\
					sent parameter is NULL.\n\
					Verify your code, it is unsafe !!!");
		return (NULL);
	}
	prepend(str, prefix);
}

#else

void			ft_strprepend(char **str, char *prefix)
{
	char	*str_new;

	str_new = ft_strjoin(prefix, *str);
	ft_strdel(str);
	*str = str_new;
}
#endif
