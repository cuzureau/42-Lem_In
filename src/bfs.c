/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:40:56 by jayache           #+#    #+#             */
/*   Updated: 2019/02/18 16:06:22 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

/*
** CLEAN THE BFS
*/

void	clean_bfs(t_lemin *l)
{
	size_t	i;
	size_t	x;

	x = 0;
	while (x < l->g->size)
	{
		i = 0;
		while (i < l->g->n[x]->edges_number)
		{
			l->g->n[x]->e[i]->added = 0;
			++i;
		}
		++x;
	}
}

/*
** BEGINNING OF BFS
*/

t_edge	**bfs_init(t_lemin *l, t_node *start, int *top, int *p)
{
	t_edge	**pile;
	size_t	pos;

	clean_bfs(l);
	*top = 0;
	*p = 0;
	pos = 0;
	if (!(pile = (t_edge**)ft_memalloc(((l->total_tubes * 2) + 1) \
		* sizeof(t_edge*))))
		exit(EXIT_FAILURE);
	while (pos < start->edges_number)
	{
		if (start->e[pos]->flow < start->e[pos]->maxflow)
		{
			pile[*top] = start->e[pos];
			++(*top);
		}
		pos++;
	}
	return (pile);
}

/*
** ADD AN EDGE ON TOP OF THE PILE
*/

void	add_to_pile(t_edge **pile, t_edge *to_add, int *top, int pos)
{
	t_edge *t;

	t = graph_find_reverse(to_add->next, to_add->prev);
	t->added = 1;
	pile[*top] = to_add;
	pile[*top]->added = 1;
	pile[*top]->prevv = pile[pos];
	++(*top);
}

/*
** SIMPLE BFS
*/

int		bfs(t_lemin *l, t_node *start)
{
	t_edge	**pile;
	int		top;
	int		pos;
	size_t	i;

	if (!(pile = bfs_init(l, start, &top, &pos)))
		return (0);
	while (pos < l->total_tubes * 2 && pile[pos])
	{
		i = 0;
		while (i < ((t_node*)(pile[pos]->next))->edges_number)
		{
			if (((t_node*)(pile[pos]->next))->i->status == R_END)
				return (activate_way(l, pile[pos], start, pile));
			if (filter(pile[pos], pile[pos]->next, i))
				add_to_pile(pile, ((t_node*)(pile[pos]->next))->e[i], &top,
						pos);
			++i;
		}
		++pos;
	}
	free(pile);
	return (0);
}
