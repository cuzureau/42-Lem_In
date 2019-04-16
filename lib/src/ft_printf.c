/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/18 10:25:44 by cuzureau          #+#    #+#             */
/*   Updated: 2018/10/18 16:54:44 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/ft_printf.h"

void			ft_rules(t_field *f)
{
	if (f->flag)
	{
		if (f->flag & PLUS && ft_strchr_index("dDi", f->type) < 0)
			f->flag &= ~PLUS;
		if (f->flag & SPACE && ft_strchr_index("dDi", f->type) < 0)
			f->flag &= ~SPACE;
		if (f->flag & MINUS)
			f->flag &= ~ZERO;
		if (f->flag & HASH && ft_strchr_index("oOxX", f->type) < 0)
			f->flag &= ~HASH;
	}
	if (ft_strchr_index("CSDOUp", f->type) >= 0)
		f->leng = 0;
	else if (f->leng & L1 && ft_strchr_index("cs", f->type) >= 0)
		f->type -= 32;
}

void			ft_parse_opt(const char *src, int *l, t_field *f)
{
	short		i;

	f->flag = 0;
	f->prec = 0;
	f->widt = 0;
	f->leng = 0;
	while (src[++(*l)] && (i = ft_strchr_index("+-#0 ", src[*l])) >= 0)
		f->flag |= (1 << i);
	while (src[*l] >= '0' && src[*l] <= '9')
		f->widt = (f->widt * 10) + src[(*l)++] - 48;
	if (src[*l] == '.')
	{
		f->flag |= DOT;
		while (src[++(*l)] >= '0' && src[*l] <= '9')
			f->prec = (f->prec * 10) + src[*l] - 48;
	}
	if ((i = ft_strchr_index("hljz", src[(*l)])) >= 0 && src[(*l)++])
		f->leng |= (1 << i);
	if ((i = ft_strchr_index("hl", src[(*l)])) >= 0 && src[(*l)++])
		f->leng |= (1 << (i + 4));
	f->type = src[*l];
	ft_rules(f);
}

void			ft_add_txt(const char *src, int *lsrc, char *dst, int *ldst)
{
	while (*ldst < BUF_SIZE && src[*lsrc] && src[*lsrc] != '%')
		dst[(*ldst)++] = src[(*lsrc)++];
	dst[*ldst] = '\0';
}

void			ft_print_buf(char *dst, int *l, int *total_len)
{
	write(1, dst, *l);
	*total_len += *l;
	dst[0] = '\0';
	*l = 0;
}

int				ft_printf(const char *format, ...)
{
	t_main		m;
	t_field		f;

	m.lsrc = 0;
	m.ldst = 0;
	m.total_len = 0;
	va_start(m.ap, format);
	ft_run(format, &m, &f);
	va_end(m.ap);
	return (m.total_len);
}
