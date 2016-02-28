/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdruel <gdruel@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/11/08 13:48:40 by gdruel            #+#    #+#             */
/*   Updated: 2015/08/27 22:21:01 by gdruel           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <string.h>
#include <stdlib.h>

static int			ft_words_counter(char const *s, char c)
{
	int i;
	int b;

	i = 0;
	b = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		while (s[i] != c && s[i] != '\0')
			i++;
		if (s[i - 1] != c)
			b++;
	}
	return (b);
}

static char			**ft_words_copyer(char const *s, char c, int w, char **tab)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (k < w)
	{
		j = 0;
		while (s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			j++;
		}
		tab[k] = ft_strsub(s, (i - j), j);
		k++;
	}
	return ((char **)tab);
}

char				**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		w;

	if (!s)
		return (NULL);
	w = ft_words_counter(s, c);
	tab = (char**)malloc(sizeof(char *) * w + 1);
	if (tab)
	{
		tab[w] = ((void*)0);
		return (ft_words_copyer(s, c, w, tab));
	}
	return (NULL);
}
