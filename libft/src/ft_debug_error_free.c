/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_debug_error_free.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 20:19:56 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/05 20:21:30 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_debug_error_free(const char *fn_name)
{
	ft_printf("\n\x1B[31mERROR in libft.a: the function %s %s\n", fn_name,
			"returned the following error:\ncandidate for free is NULL. \
			Verify your code, it is unsafe !!!\x1B[0m");
}
