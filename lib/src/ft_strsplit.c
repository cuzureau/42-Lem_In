/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 14:14:21 by jayache           #+#    #+#             */
/*   Updated: 2019/01/14 15:16:56 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../inc/libft.h"

static unsigned int		wordcount(char const *s, char c)
{
	unsigned int x;
	unsigned int count;
	unsigned int inword;

	inword = 0;
	count = 0;
	x = 0;
	while (s[x])
	{
		while (s[x] && s[x] != c)
		{
			++x;
			if (!inword)
			{
				inword = 1;
				count++;
			}
		}
		inword = 0;
		while (s[x] && s[x] == c)
			++x;
	}
	return (count);
}

static unsigned int		nextword(char const *s, char c, unsigned int pos)
{
	while (s[pos])
	{
		if (s[pos] != c)
			return (pos);
		++pos;
	}
	return (0);
}

static unsigned int		sizenextword(char const *s, char c, unsigned int pos)
{
	unsigned int size;

	size = 0;
	while (s[pos])
	{
		while (s[pos] != c && s[pos])
		{
			++size;
			++pos;
		}
		if (size)
			return (size);
		++pos;
	}
	return (0);
}

char					**ft_strsplit(char const *s, char c)
{
	char				**str;
	unsigned int		x;
	unsigned int		pos;

	if (!s)
		return (NULL);
	pos = 0;
	x = 0;
	str = (char**)malloc(sizeof(char*) * (wordcount(s, c) + 1));
	if (!str)
		return (NULL);
	while (x < wordcount(s, c))
	{
		str[x] = ft_strsub(s, nextword(s, c, pos),
		(size_t)sizenextword(s, c, pos));
		pos = nextword(s, c, pos) + sizenextword(s, c, pos);
		++x;
	}
	str[x] = NULL;
	return (str);
}
