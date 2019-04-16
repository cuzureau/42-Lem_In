/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_node_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 11:33:33 by jayache           #+#    #+#             */
/*   Updated: 2019/01/24 10:19:03 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

t_node			*ft_graph_node_search(t_graph *g, char *name)
{
	size_t		x;

	x = 0;
	while (x < g->size)
	{
		if (g->n[x] != NULL && g->n[x]->i && ft_strequ(g->n[x]->i->name, name))
			return (g->n[x]);
		++x;
	}
	return (NULL);
}
