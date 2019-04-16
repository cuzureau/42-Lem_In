/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   letters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:47:48 by cuzureau          #+#    #+#             */
/*   Updated: 2019/01/24 15:00:50 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

short			ft_wlen(wchar_t wc)
{
	if (wc <= 0x7F)
		return (1);
	if (wc <= 0x7FF)
		return (2);
	if (wc <= 0xFFFF)
		return (3);
	return (4);
}

void			ft_wconv1(char *dst, int *ldst, wchar_t wc, short wlen)
{
	if (wlen == 1)
		dst[(*ldst)++] = wc;
	else if (wlen == 2)
	{
		dst[(*ldst)++] = (wc >> 6) + 0xC0;
		dst[(*ldst)++] = (wc & 0x3F) + 0x80;
	}
	else if (wlen == 3)
	{
		dst[(*ldst)++] = (wc >> 12) + 0xE0;
		dst[(*ldst)++] = ((wc >> 6) & 0x3F) + 0x80;
		dst[(*ldst)++] = (wc & 0x3F) + 0x80;
	}
	else
	{
		dst[(*ldst)++] = (wc >> 18) + 0xF0;
		dst[(*ldst)++] = ((wc >> 12) & 0x3F) + 0x80;
		dst[(*ldst)++] = ((wc >> 6) & 0x3F) + 0x80;
		dst[(*ldst)++] = (wc & 0x3F) + 0x80;
	}
}

void			ft_wconv2(t_main *m, wchar_t wc)
{
	size_t		wlen;

	wlen = ft_wlen(wc);
	if (wlen > (size_t)(BUF_SIZE - m->ldst))
		ft_print_buf(m->dst, &m->ldst, &m->total_len);
	ft_wconv1(m->dst, &m->ldst, wc, wlen);
}

void			ft_add_letter(t_field *f, t_main *m)
{
	char		c;
	char		*s;
	size_t		l;

	if (f->type == 'c')
	{
		c = va_arg(m->ap, int);
		if (!(f->flag & MINUS))
			ft_fill(m, (f->flag & ZERO ? '0' : ' '), (f->widt - 1));
		ft_fill(m, c, 1);
		f->flag & MINUS ? ft_fill(m, ' ', (f->widt - 1)) : 0;
	}
	else if (f->type == 's')
	{
		s = va_arg(m->ap, char*);
		s == NULL ? s = "(null)\0" : 0;
		l = (f->flag & DOT && f->prec < (int)ft_slen(s) ? f->prec : ft_slen(s));
		if (!(f->flag & MINUS))
			ft_fill(m, (f->flag & ZERO ? '0' : ' '), f->widt - l);
		ft_add(s, l, m);
		if (f->flag & MINUS)
			ft_fill(m, ' ', f->widt - l);
	}
	else
		ft_wletter(f, m);
}

void			ft_wletter(t_field *f, t_main *m)
{
	wchar_t		wc;
	size_t		wlen;

	if (f->type == 'C')
	{
		wc = va_arg(m->ap, wchar_t);
		wlen = ft_wlen(wc);
		if (!(f->flag & MINUS))
			ft_fill(m, ' ', f->widt - wlen);
		ft_wconv2(m, wc);
		if (f->flag & MINUS)
			ft_fill(m, ' ', f->widt - wlen);
	}
	else if (f->type == 'S')
		ft_big_s(f, m);
}
