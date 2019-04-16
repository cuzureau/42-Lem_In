/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 12:25:26 by cuzureau          #+#    #+#             */
/*   Updated: 2019/02/18 16:00:44 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

int				ft_parse_infos(t_lemin *l)
{
	t_info				*i;
	unsigned char		tmp;

	i = NULL;
	if (ft_strequ(l->line, "##start") || ft_strequ(l->line, "##end"))
	{
		if (ft_strequ(l->line, "##start"))
		{
			tmp = R_START;
			++l->is_start;
		}
		else if (ft_strequ(l->line, "##end"))
		{
			tmp = R_END;
			++l->is_end;
		}
		buffer_add_lign(l->buff, l->line);
		if (get_next_line(0, &l->line) > 0)
			i = ft_parse_rooms(l);
		if (!i)
			return (0);
		i->status = tmp;
	}
	return (1);
}

int				ft_parse_ants(t_lemin *l)
{
	while (get_next_line(0, &l->line) > 0 && l->line[0] == '#')
	{
		if (ft_strequ(l->line, "##start") || ft_strequ(l->line, "##end"))
			ft_exit_clean(l);
		buffer_add_lign(l->buff, l->line);
	}
	l->total_ants = ft_atoi(l->line);
	if (l->total_ants <= 0)
		ft_exit_clean(l);
	buffer_add_lign(l->buff, l->line);
	return (1);
}

int				ft_parse_tubes(t_lemin *l)
{
	t_node		*a;
	t_node		*b;
	char		**names;

	if (ft_strchr_num(l->line, '-') != 1 \
			|| !(names = ft_strsplit(l->line, '-')))
		return (0);
	if (!ft_len_tab(names, 2))
	{
		ft_free_tab(names, 2);
		return (0);
	}
	if (ft_strequ(names[0], names[1]))
		return (0);
	a = ft_graph_node_search(l->g, names[0]);
	b = ft_graph_node_search(l->g, names[1]);
	ft_free_tab(names, 2);
	if (!a || !b)
		return (0);
	if (graph_find_reverse(a, b))
		return (1);
	++l->total_tubes;
	if (!(ft_graph_add_link(a, b)))
		return (0);
	return (1);
}

t_info			*ft_parse_rooms(t_lemin *l)
{
	t_info		*i;
	char		**tab;

	if (l->total_tubes != 0 || l->line[0] == 'L' || l->line[0] == '#')
		return (NULL);
	if (!(i = ft_memalloc(sizeof(t_info))))
		exit(EXIT_FAILURE);
	if (ft_strchr_num(l->line, ' ') != 2)
	{
		ft_memdel((void*)&i);
		return (NULL);
	}
	if (!(tab = ft_strsplit(l->line, ' ')))
		return (NULL);
	if (!ft_len_tab(tab, 3))
	{
		ft_memdel((void*)&i);
		ft_free_tab(tab, 3);
		return (NULL);
	}
	ft_fill_node(l, i, tab);
	++l->total_rooms;
	return (i);
}

void			ft_parse(t_lemin *l)
{
	int					ret;

	if (!(l->g = ft_graph_new()))
		exit(EXIT_FAILURE);
	ret = ft_parse_ants(l);
	while (get_next_line(0, &l->line) > 0)
	{
		if (l->line[0] == '#')
			ret = ft_parse_infos(l);
		else if (ft_strchr(l->line, '-'))
			ret = ft_parse_tubes(l);
		else if (ft_strchr(l->line, ' '))
			ret = (int)ft_parse_rooms(l);
		else
			break ;
		if (ret != 0)
			buffer_add_lign(l->buff, l->line);
		else
			break ;
	}
	ft_check_posibility(l);
}
