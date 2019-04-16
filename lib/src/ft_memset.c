/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 11:58:31 by jayache           #+#    #+#             */
/*   Updated: 2019/01/03 14:44:19 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memset(void *b, unsigned char c, size_t len)
{
	unsigned char *str;

	str = (unsigned char*)b;
	while (len)
	{
		(*(str + len - 1)) = c;
		len--;
	}
	return (str);
}
