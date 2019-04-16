/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/09 15:42:39 by cuzureau          #+#    #+#             */
/*   Updated: 2019/01/24 15:00:24 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void		ft_get_signed(intmax_t *nb, char type, char leng, va_list ap)
{
	if (leng == 0)
	{
		if (type == 'D')
			*nb = va_arg(ap, long);
		else
			*nb = va_arg(ap, int);
	}
	else
	{
		if (leng & L2)
			*nb = va_arg(ap, long long);
		else if (leng & H2)
			*nb = (char)va_arg(ap, int);
		else if (leng & L1)
			*nb = va_arg(ap, long);
		else if (leng & H1)
			*nb = (short)va_arg(ap, int);
		else if (leng & J)
			*nb = va_arg(ap, intmax_t);
		else if (leng & Z)
			*nb = va_arg(ap, size_t);
	}
}

void		ft_get_unsigned(uintmax_t *unb, char type, char leng, va_list ap)
{
	if (leng == 0)
	{
		if (ft_strchr_index("OUp", type) >= 0)
			*unb = va_arg(ap, unsigned long);
		else
			*unb = va_arg(ap, unsigned int);
	}
	else
	{
		if (leng & L2)
			*unb = va_arg(ap, unsigned long long);
		else if (leng & H2)
			*unb = (unsigned char)va_arg(ap, int);
		else if (leng & L1)
			*unb = va_arg(ap, unsigned long);
		else if (leng & H1)
			*unb = (unsigned short)va_arg(ap, int);
		else if (leng & J)
			*unb = va_arg(ap, uintmax_t);
		else if (leng & Z)
			*unb = va_arg(ap, size_t);
	}
}

void		ft_base_and_index(short neg, char type, short *base, char **index)
{
	if (ft_strchr_index("duDUi", type) >= 0)
	{
		*base = 10;
		*index = "0123456789";
	}
	else if (ft_strchr_index("xXp", type) >= 0)
	{
		*base = 16;
		*index = (type == 'X' ? "0123456789ABCDEF" : "0123456789abcdef");
	}
	else if (ft_strchr_index("oO", type) >= 0)
	{
		*base = 8;
		*index = "01234567";
	}
	else if (type == 'b')
	{
		*base = 2;
		*index = (neg == 1 ? "01" : "10");
	}
}

void		ft_conv_base(short neg, t_field *f, char **start, uintmax_t value)
{
	short		base;
	char		*index;

	ft_base_and_index(neg, f->type, &base, &index);
	*(*start) = '\0';
	if (value == 0 && (!(f->flag & DOT) || (f->flag & DOT && f->prec > 0) || \
			(f->flag & HASH && (f->type == 'o' || f->type == 'O'))))
		*--(*start) = '0';
	while (value != 0)
	{
		*--(*start) = index[(value % base)];
		value /= base;
	}
}

void		ft_add_number(t_field *f, t_main *m)
{
	t_number	n;

	ft_get_number(&n, m, f);
	ft_prefix(&n, f);
	if (f->prec < ((int)ft_slen(n.start) + (int)ft_slen(n.prefix)))
		n.len = f->widt - (ft_slen(n.prefix) + ft_slen(n.start));
	else
		n.len = f->widt - f->prec - ft_slen(n.prefix);
	if (!(f->flag & MINUS))
	{
		if (!(f->flag & ZERO) || (f->flag & ZERO && f->prec > 0))
			ft_fill(m, ' ', n.len);
		ft_add(n.prefix, ft_slen(n.prefix), m);
		if (f->prec > 0)
			ft_fill(m, '0', f->prec - ft_slen(n.start) - \
					(f->type == 'o' && f->flag & HASH ? 1 : 0));
		f->prec <= 0 && f->flag & ZERO ? ft_fill(m, '0', n.len) : 0;
	}
	else
	{
		ft_add(n.prefix, ft_slen(n.prefix), m);
		f->prec > 0 ? ft_fill(m, '0', (f->prec - ft_slen(n.start))) : 0;
	}
	ft_add(n.start, ft_slen(n.start), m);
	f->flag & MINUS ? ft_fill(m, ' ', n.len) : 0;
}
