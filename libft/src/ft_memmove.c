/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 12:37:16 by tdefresn          #+#    #+#             */
/*   Updated: 2015/12/14 11:51:53 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	copy_forward_if_t(char *ptr_dst, const char *ptr_src, size_t t)
{
	if (t)
		while (t--)
			*ptr_dst++ = *ptr_src++;
	return (t);
}

static void		move_forward(char *ptr_dst, const char *ptr_src,
								size_t len, size_t t)
{
	t = (int)ptr_src;
	if ((t | (int)ptr_dst) & (sizeof(int) - 1))
	{
		if ((t ^ (int)ptr_dst) & (sizeof(int) - 1) || len < sizeof(int))
			t = len;
		else
			t = sizeof(int) - (t & (sizeof(int) - 1));
		len -= t;
		while (t--)
			*ptr_dst++ = *ptr_src++;
	}
	t = len / sizeof(int);
	if (t)
	{
		while (t--)
		{
			*(int *)ptr_dst = *(int *)ptr_src;
			ptr_src += sizeof(int);
			ptr_dst += sizeof(int);
		}
	}
	t = len & sizeof(int);
	t = copy_forward_if_t(ptr_dst, ptr_src, t);
}

static size_t	copy_backward_if_t(char *ptr_dst, const char *ptr_src, size_t t)
{
	if (t)
		while (t--)
			*--ptr_dst = *--ptr_src;
	return (t);
}

static void		move_backward(char *ptr_dst, const char *ptr_src,
								size_t len, size_t t)
{
	ptr_src += len;
	ptr_dst += len;
	t = (int)ptr_src;
	if ((t | (int)ptr_dst) & (sizeof(int) - 1))
	{
		if ((t ^ (int)ptr_dst) & (sizeof(int) - 1) || len <= sizeof(int))
			t = len;
		else
			t &= (sizeof(int) - 1);
		len -= t;
		while (t--)
			*--ptr_dst = *--ptr_src;
	}
	t = len / sizeof(int);
	if (t)
	{
		while (t--)
		{
			ptr_src -= sizeof(int);
			ptr_dst -= sizeof(int);
			*(int *)ptr_dst = *(int *)ptr_src;
		}
	}
	t = len & (sizeof(int) - 1);
	t = copy_backward_if_t(ptr_dst, ptr_src, t);
}

void			*ft_memmove(void *dst, void const *src, size_t len)
{
	char		*ptr_dst;
	const char	*ptr_src;

	if (len == 0 || dst == src)
		return (dst);
	ptr_dst = (char *)dst;
	ptr_src = (const char *)src;
	if ((unsigned long)ptr_dst < (unsigned long)ptr_src)
		move_forward(ptr_dst, ptr_src, len, 0);
	else
		move_backward(ptr_dst, ptr_src, len, 0);
	return (dst);
}
