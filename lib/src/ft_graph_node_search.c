/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_node_search.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 16:54:55 by jayache           #+#    #+#             */
/*   Updated: 2019/01/01 17:21:16 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_node	*ft_graph_node_search(t_graph *graph, int (*f)(void *elem, void *elem))
{
	int x;

	x = 0;
	while (x < graph->size)
	{
		if (f(graph->nodes[x]->elem, elem) == 1)
			return (graph->nodes[x]);
		++x;
	}
	return (NULL);
}
