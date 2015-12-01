/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:36:01 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/01 12:36:07 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

static void		clear_words_table(char **words_table, int last_idx)
{
	int i;

	i = 0;
	while (i < last_idx)
		ft_strdel(&words_table[i++]);
	ft_memdel((void**)&words_table);
}

static int		init_list_elem(unsigned int len, t_list **words_list)
{
	(*words_list)->next = (t_list *)malloc(sizeof(t_list));
	if ((*words_list)->next == NULL)
		return (1);
	(*words_list)->content_size = len;
	*words_list = (*words_list)->next;
	(*words_list)->content = NULL;

	return (0);
}

static void		clear_list(t_list *words_list)
{
	if (words_list->next)
		clear_list(words_list->next);
	free(words_list);
}

static unsigned int	count_words(char const *s, char c, t_list *words_list)
{
	unsigned int count;
	unsigned int len;

	count = 0;
	len = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			if (len > 0)
			{
				if ((init_list_elem(len, &words_list)) != 0)
					return (0);
				len = 0;
				count++;
			}
		}
		else
		{
			if (words_list->content == NULL)
				words_list->content = (void *)s;
			len++;
		}
		s++;
	}
	if (len > 0)
	{
		if ((init_list_elem(len, &words_list)) != 0)
			return (0);
		count++;
	}

	return (count);
}

static void	split_words(char **words_table, t_list *words_list)
{
	int	i;

	i = 0;
	while (words_list != NULL)
	{
		words_table[i] = ft_strsub((char *)words_list->content, 
						0, words_list->content_size);
		if (words_table[i] == NULL)
		{
			clear_words_table(words_table, i);
			return;
		}
		words_table[i][words_list->content_size] = '\0';
		words_list = words_list-> next;
		i++;
	}
}

char	**ft_strsplit(char const *s, char c)
{
	int		words_count;
	char		**words_table;
	t_list		*words_list;

	words_list = (t_list *)malloc(sizeof(t_list));
	words_list->content = NULL;
	words_count = count_words(s, c, words_list);
	words_table = (char **)malloc(sizeof(char *) * (words_count + 1));
	if (words_table)
	{
		if (words_count > 0)
			split_words(words_table, words_list);
		words_table[words_count] = (char *)malloc(sizeof(char *));
		words_table[words_count][0] = '\0';
	}
	if (words_list)
		clear_list(words_list);
	return (words_table);
}
