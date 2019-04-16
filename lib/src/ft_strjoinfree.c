/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoinfree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:41:01 by cuzureau          #+#    #+#             */
/*   Updated: 2018/12/18 13:41:05 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char		*ft_strjoinfree(char *s1, char const *s2)
{
	int		size;
	char	*new;
	int		i;
	int		j;

	i = -1;
	j = 0;
	if (!s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	size = ft_strlen(s1) + ft_strlen(s2);
	if ((new = malloc(sizeof(char) * (size + 1))) == 0)
		return (NULL);
	new[size] = '\0';
	while (s1[++i])
		new[i] = s1[i];
	while (s2[j])
	{
		new[i] = s2[j];
		i++;
		j++;
	}
	ft_strdel(&s1);
	return (new);
}
