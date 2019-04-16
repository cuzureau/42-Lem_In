/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <cuzureau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/20 13:47:50 by cuzureau          #+#    #+#             */
/*   Updated: 2019/01/24 14:56:55 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <limits.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <locale.h>

# define BUF_SIZE 4096
# define CONV_SIZE 96

# define PLUS (1 << 0)
# define MINUS (1 << 1)
# define HASH (1 << 2)
# define ZERO (1 << 3)
# define SPACE (1 << 4)
# define DOT (1 << 5)

# define H1 (1 << 0)
# define L1 (1 << 1)
# define J (1 << 2)
# define Z (1 << 3)
# define H2 (1 << 4)
# define L2 (1 << 5)

typedef struct	s_field
{
	int			widt;
	int			prec;
	char		flag;
	char		leng;
	char		type;
}				t_field;

typedef struct	s_main
{
	va_list		ap;
	char		dst[BUF_SIZE];
	int			lsrc;
	int			ldst;
	int			total_len;
}				t_main;

typedef struct	s_number
{
	intmax_t	nb;
	uintmax_t	unb;
	char		buf[CONV_SIZE];
	char		*start;
	short		len;
	char		prefix[3];
}				t_number;

void			ft_rules(t_field *f);
void			ft_parse_opt(const char *src, int *l, t_field *f);
void			ft_add_txt(const char *src, int *lsrc, char *dst, int *ldst);
void			ft_print_buf(char *dst, int *l, int *total_len);
int				ft_printf(const char *format, ...);

size_t			ft_slen(char *str);
short			ft_strchr_index(char *index, char c);
void			ft_fill(t_main *m, char c, int n);
void			ft_add(char *src, int len, t_main *m);
void			ft_add_other(char c, t_field *f, t_main *m);

void			ft_get_signed(intmax_t *nb, char type, char leng, va_list ap);
void			ft_get_unsigned(uintmax_t *unb, char type, char leng, \
		va_list ap);
void			ft_base_and_index(short neg, char type, short *base, \
		char **index);
void			ft_conv_base(short neg, t_field *f, char **start, \
		uintmax_t value);
void			ft_add_number(t_field *f, t_main *m);
void			ft_padding(t_field *f, t_main *m, size_t len);

short			ft_wlen(wchar_t wc);
void			ft_wconv1(char *dst, int *ldst, wchar_t wc, short wlen);
void			ft_wconv2(t_main *m, wchar_t wc);
void			ft_add_letter(t_field *f, t_main *m);
void			ft_wletter(t_field *f, t_main *m);

void			ft_run(const char *format, t_main *m, t_field *f);
void			ft_big_s(t_field *f, t_main *m);
void			ft_prefix(t_number *n, t_field *f);
void			ft_prefix2(t_number *n, t_field *f);
void			ft_get_number(t_number *n, t_main *m, t_field *f);
#endif
