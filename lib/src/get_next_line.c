/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/11 13:04:52 by jayache           #+#    #+#             */
/*   Updated: 2019/01/01 16:30:10 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	include "../inc/libft.h"

static char		*strjjoin(char *s1, char *s2, size_t x, int cut)
{
	char *str;

	if (!(str = ft_strnew(ft_strlen(s1) + x)))
		return (NULL);
	ft_strcat(str, s1);
	if (!cut)
		ft_strcat(str, s2);
	else
		ft_strncat(str, s2, x);
	if (s1)
		free(s1);
	return (str);
}

static int		ft_readfile(char **tab, char **line, const int fd)
{
	ssize_t	status;
	size_t	x;

	status = 1;
	x = 0;
	while ((*tab)[x] != '\n')
	{
		++x;
		if ((*tab)[x] == '\0')
		{
			if (!(*line = strjjoin(*line, *tab, x, 0)))
				return (-1);
			ft_bzero(*tab, BUFF_SIZE);
			if ((status = read(fd, *tab, BUFF_SIZE)) == 0)
				return (*line[0] != '\0');
			else if (status == -1)
				return (-1);
			x = 0;
		}
	}
	if (!(*line = strjjoin(*line, *tab, x, 1)))
		return (-1);
	ft_memmove(*tab, *tab + x + 1, BUFF_SIZE - x);
	(*tab)[BUFF_SIZE - x] = '\0';
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static	char	*tab[MAX_OPEN];

	if (fd < 0 || !line || BUFF_SIZE <= 0)
		return (-1);
	if (!(*line = ft_strnew(0)))
		return (-1);
	if (read(fd, line, 0) == -1)
		return (-1);
	if (!tab[fd])
		if (!(tab[fd] = ft_strnew(sizeof(char) * BUFF_SIZE)))
			return (-1);
	return (ft_readfile(&(tab[fd]), line, fd));
}
