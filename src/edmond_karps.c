/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edmond_karps.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/23 15:55:55 by jayache           #+#    #+#             */
/*   Updated: 2019/01/29 14:09:49 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

/*
** update an edge
*/

void	update_flow(t_edge *e)
{
	t_edge *t;

	e->flow += 1;
	t = graph_find_reverse(e->next, e->prev);
	t->flow -= 1;
	if (e->flow > 1 || t->flow < -1)
		ft_exit_clean();
}

/*
** Initie l'algo pour l'instant
*/

int		ft_init_algo(t_lemin *l)
{
	t_node		*start;
	t_node		*end;
	int			i;
	int			maxflow;
	t_edge		*t;

	maxflow = 0;
	if (!(start = ft_graph_node_search_type(l->g, R_START)))
		return (0);
	if (!(end = ft_graph_node_search_type(l->g, R_END)))
		return (0);
	l->path = (t_edge**)ft_memalloc(sizeof(t_edge*) * (l->total_tubes + 2));
	while (bfs(l, start))
	{
		i = 0;
		while (l->path[i])
			update_flow(l->path[i++]);
		if ((t = graph_find_reverse(start, l->path[0]->prev)))
			t->flow += 1;
		if ((t = graph_find_reverse(l->path[0]->prev, start)))
			t->flow -= 1;
		maxflow += 1;
		addbundle(l, maxflow);
	}
	return (maxflow);
}
