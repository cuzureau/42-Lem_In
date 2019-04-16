/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 15:22:19 by jayache           #+#    #+#             */
/*   Updated: 2019/01/27 11:40:02 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

static void	copy_buffer(char **dest, char **src, int size)
{
	int i;

	i = 0;
	if (!src)
		return ;
	while (i < size && src[i])
	{
		dest[i] = src[i];
		++i;
	}
}

void		buffer_add_lign(t_buffer *buf, char *lign)
{
	char	**tmp;

	if (buf->pos + 1 >= buf->size)
	{
		if (!(tmp = (char**)ft_memalloc((buf->size + 1000) * sizeof(char*))))
			exit(EXIT_FAILURE);
		copy_buffer(tmp, buf->buffer, buf->size + 1000);
		if (buf->buffer)
			free(buf->buffer);
		buf->buffer = tmp;
		buf->size += 1000;
	}
	buf->buffer[buf->pos] = lign;
	buf->pos += 1;
}
