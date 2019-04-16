/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:42:13 by cuzureau          #+#    #+#             */
/*   Updated: 2018/12/18 13:42:17 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

char	*ft_strndup(const char *src, int n)
{
	int		i;
	int		a;
	char	*dup;

	i = 0;
	a = 0;
	while (src[i] && i < n)
		i++;
	if ((dup = malloc(sizeof(char) * (i + 1))) == 0)
		return (NULL);
	while (a < i)
	{
		dup[a] = src[a];
		a++;
	}
	dup[a] = '\0';
	return (dup);
}
