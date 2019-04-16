/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 11:12:33 by cuzureau          #+#    #+#             */
/*   Updated: 2019/01/24 14:59:46 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void		ft_run(const char *format, t_main *m, t_field *f)
{
	while (format[m->lsrc])
	{
		if (format[m->lsrc] == '%')
		{
			if (format[m->lsrc + 1] != '\0')
			{
				ft_parse_opt(format, &m->lsrc, f);
				if (ft_strchr_index("scSC", f->type) >= 0)
					ft_add_letter(f, m);
				else if (ft_strchr_index("dxoupDUOXbi", f->type) >= 0)
					ft_add_number(f, m);
				else
					ft_add_other(format[m->lsrc], f, m);
			}
			m->lsrc++;
		}
		else
			ft_add_txt(format, &m->lsrc, m->dst, &m->ldst);
		if (format[m->lsrc] == '\0' || m->ldst == BUF_SIZE)
			ft_print_buf(m->dst, &m->ldst, &m->total_len);
	}
}

void		ft_big_s(t_field *f, t_main *m)
{
	size_t	i;
	wchar_t	*wstr;
	size_t	wstrlen;

	i = 0;
	wstrlen = 0;
	wstr = va_arg(m->ap, wchar_t*);
	if (!wstr)
		wstr = L"(null)\0";
	while (wstr[i])
		wstrlen += ft_wlen(wstr[i++]);
	if (f->flag & DOT)
		wstrlen = 0;
	if (!(f->flag & MINUS))
		ft_fill(m, (f->flag & ZERO ? '0' : ' '), f->widt - wstrlen);
	if (!(f->flag & DOT))
	{
		while (*wstr)
			ft_wconv2(m, *wstr++);
	}
	if (f->flag & MINUS)
		ft_fill(m, (f->flag & ZERO ? '0' : ' '), f->widt - wstrlen);
}

void		ft_prefix2(t_number *n, t_field *f)
{
	if (n->nb > 0 || n->unb > 0)
	{
		if (f->flag & HASH)
		{
			if (ft_strchr_index("xX", f->type) >= 0)
			{
				n->prefix[0] = '0';
				n->prefix[1] = (f->type == 'x' ? 'x' : 'X');
			}
			else if (ft_strchr_index("oO", f->type) >= 0)
				n->prefix[0] = '0';
		}
		else if (f->flag & SPACE || f->flag & PLUS)
			n->prefix[0] = (f->flag & PLUS ? '+' : ' ');
	}
	else
	{
		if (f->flag & SPACE || f->flag & PLUS)
			n->prefix[0] = (f->flag & PLUS ? '+' : ' ');
	}
}

void		ft_prefix(t_number *n, t_field *f)
{
	n->prefix[0] = '\0';
	n->prefix[1] = '\0';
	n->prefix[2] = '\0';
	if (f->type == 'p')
	{
		n->prefix[0] = '0';
		n->prefix[1] = 'x';
	}
	else if (n->nb < 0)
	{
		if (f->type != 'b')
			n->prefix[0] = '-';
		else
			n->buf[CONV_SIZE - 2] = (n->buf[CONV_SIZE - 2] == '0' ? '1' : '0');
	}
	else
		ft_prefix2(n, f);
}

void		ft_get_number(t_number *n, t_main *m, t_field *f)
{
	n->nb = 0;
	n->unb = 0;
	if (ft_strchr_index("dDbi", f->type) >= 0)
		ft_get_signed(&n->nb, f->type, f->leng, m->ap);
	else
		ft_get_unsigned(&n->unb, f->type, f->leng, m->ap);
	n->start = &n->buf[CONV_SIZE - 1];
	if (n->nb < 0)
		ft_conv_base(-1, f, &n->start, -(n->nb));
	else if (n->nb > 0 || n->unb > 0)
		ft_conv_base(1, f, &n->start, (n->nb != 0 ? n->nb : n->unb));
	else
		ft_conv_base(0, f, &n->start, 0);
}
