/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 08:57:00 by cuzureau          #+#    #+#             */
/*   Updated: 2019/01/03 14:55:01 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memalloc(size_t size)
{
	void	*str;

	if (!(str = (void *)malloc(size)))
		return (0);
	ft_bzero(str, size);
	return (str);
}
