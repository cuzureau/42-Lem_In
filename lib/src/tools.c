/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:50:04 by cuzureau          #+#    #+#             */
/*   Updated: 2019/01/24 14:56:22 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

short			ft_strchr_index(char *index, char c)
{
	short		i;

	i = 0;
	while (index[i])
	{
		if (index[i] == c)
			return (i);
		i++;
	}
	return (-1);
}

size_t			ft_slen(char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

void			ft_fill(t_main *m, char c, int n)
{
	while (n > 0)
	{
		m->dst[m->ldst] = c;
		n--;
		m->ldst++;
		if (m->ldst == BUF_SIZE)
			ft_print_buf(m->dst, &m->ldst, &m->total_len);
	}
	m->dst[m->ldst] = '\0';
}

void			ft_add(char *src, int len, t_main *m)
{
	int			i;

	i = 0;
	while (src[i] && i < len)
	{
		while (m->ldst < BUF_SIZE && src[i] && i < len)
			m->dst[m->ldst++] = src[i++];
		m->dst[m->ldst] = '\0';
		if (m->ldst == BUF_SIZE)
			ft_print_buf(m->dst, &m->ldst, &m->total_len);
	}
}

void			ft_add_other(char c, t_field *f, t_main *m)
{
	if (!(f->flag & MINUS))
		ft_fill(m, (f->flag & ZERO ? '0' : ' '), (f->widt - 1));
	ft_fill(m, c, 1);
	if (f->flag & MINUS)
		ft_fill(m, (f->flag & ZERO ? '0' : ' '), (f->widt - 1));
}
