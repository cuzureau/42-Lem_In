/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/03 10:57:14 by jayache           #+#    #+#             */
/*   Updated: 2019/02/18 16:06:42 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

/*
**	test if the node is already used by another track
** making an exception if we are currently backtracking
*/

static int		has_positive_flow(t_edge *edge, t_node *node)
{
	size_t	i;

	i = 0;
	if (edge->flow == -1)
		return (0);
	while (i < node->edges_number)
	{
		if (node->e[i]->flow > 0)
			return (1);
		++i;
	}
	return (0);
}

/*
** I forgot what it exactly is a good neighbor, but this function
** definitely remembers it
*/

int				filter(t_edge *edge, t_node *node, size_t neighbor)
{
	if (node == NULL || node->e == NULL || node->edges_number <= neighbor)
		return (0);
	else if (node->e[neighbor] == NULL || node->i == NULL)
		return (0);
	else if (has_positive_flow(edge, node) && node->e[neighbor]->flow >= 0)
		return (0);
	else if (node->e[neighbor]->flow < node->e[neighbor]->maxflow \
			&& node->e[neighbor]->added != 1)
		return (1);
	else
		return (0);
}

/*
** very convenient
*/

static int		free_and_return(void *ptr)
{
	ft_memdel((void*)&ptr);
	return (1);
}

/*
** validate the good way
*/

int				activate_way(t_lemin *l, t_edge *end, t_node *start,
				t_edge **pile)
{
	t_edge	*current;
	t_edge	*tmp;
	int		i;
	int		x;

	x = 0;
	i = 1;
	l->path[0] = end;
	if (!(current = end->prevv))
		return (free_and_return(pile));
	while (current && current->prev != start)
	{
		l->path[i] = current;
		current = current->prevv;
		++i;
	}
	--i;
	while (x - 1 < i / 2)
	{
		tmp = l->path[i - x];
		l->path[i - x] = l->path[x];
		l->path[x] = tmp;
		++x;
	}
	return (free_and_return(pile));
}
