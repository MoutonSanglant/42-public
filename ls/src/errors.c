/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tdefresn <tdefresn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/05 17:15:49 by tdefresn          #+#    #+#             */
/*   Updated: 2016/03/05 17:45:41 by tdefresn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "ft_ls.h"

void	error_errno()
{
	ft_printf("Error: %i\n", errno);
	exit(errno);
}

void	error_usage(int c)
{
	ft_printf("ft_ls: illegal option -- %c\nusage: ./ft_ls [-%s] [file ...]\n", c, VALID_FLAGS);
	exit(-1);
}
