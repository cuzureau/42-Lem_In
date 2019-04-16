/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 12:12:38 by cuzureau          #+#    #+#             */
/*   Updated: 2019/02/05 11:48:33 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

unsigned char	ft_len_tab(char **tab, size_t num)
{
	size_t			len;

	len = 0;
	if (!tab)
		return (0);
	while (tab[len])
		++len;
	return (len != num ? 0 : 1);
}

int				ft_strchr_num(char *str, char c)
{
	int			i;
	int			num;

	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] == c)
			++num;
		++i;
	}
	return (num);
}

void			ft_free_tab(char **tab, int size)
{
	int			i;

	i = 0;
	while (i < size)
	{
		ft_memdel((void*)&tab[i]);
		++i;
	}
	ft_memdel((void*)&tab);
}

void			ft_fill_node(t_lemin *l, t_info *i, char **tab)
{
	i->name = ft_strdup(tab[0]);
	i->x = (int)ft_atoi(tab[1]);
	i->y = (int)ft_atoi(tab[2]);
	ft_free_tab(tab, 3);
	i->status = R_NORMAL;
	if (!(ft_graph_add_node(l->g, ft_graph_node_new(i, sizeof(t_info)))))
		exit(EXIT_FAILURE);
}
