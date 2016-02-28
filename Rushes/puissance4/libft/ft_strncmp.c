/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/04 13:30:06 by gdruel            #+#    #+#             */
/*   Updated: 2015/01/27 17:36:54 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;

	i = 0;
	if (!s1 && s2)
		return (-(unsigned char)s2[i]);
	if (!s2 && s1)
		return ((unsigned char)s1[i]);
	if ((!s1 && !s2) || n == 0)
		return (0);
	while ((s1[i] == s2[i]) && (i + 1) < n && s1[i])
		i++;
	if (i == n)
		return (0);
	else
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
