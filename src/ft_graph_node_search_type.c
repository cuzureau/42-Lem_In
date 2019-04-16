/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_node_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/02 11:33:33 by jayache           #+#    #+#             */
/*   Updated: 2019/01/19 17:23:11 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

t_node			*ft_graph_node_search_type(t_graph *g, unsigned char status)
{
	size_t		x;

	x = 0;
	while (x < g->size)
	{
		if (g->n[x] != NULL && g->n[x]->i && g->n[x]->i->status == status)
			return (g->n[x]);
		++x;
	}
	return (NULL);
}
