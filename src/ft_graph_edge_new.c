/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 11:05:19 by jayache           #+#    #+#             */
/*   Updated: 2019/01/25 14:44:24 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

t_edge			*ft_graph_edge_new(t_node *a, t_node *b)
{
	t_edge		*e;

	if (!(e = (t_edge*)ft_memalloc(sizeof(t_edge))))
		exit(EXIT_FAILURE);
	e->flow = 0;
	e->maxflow = 1;
	e->prev = a;
	e->next = b;
	return (e);
}
