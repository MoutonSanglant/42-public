/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strclr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/06 17:42:36 by gdruel            #+#    #+#             */
/*   Updated: 2014/11/07 14:55:32 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strclr(char *s)
{
	int i;
	int	len;

	i = 0;
	len = ft_strlen(s);
	while (i != len)
	{
		s[i] = '\0';
		i++;
	}
}