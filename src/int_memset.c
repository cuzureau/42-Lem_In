/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_memset.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 16:12:57 by jayache           #+#    #+#             */
/*   Updated: 2019/01/28 16:13:13 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

void		int_memset(int *ptr, int val, int size)
{
	int i;

	i = 0;
	while (i < size)
	{
		ptr[i] = val;
		++i;
	}
}