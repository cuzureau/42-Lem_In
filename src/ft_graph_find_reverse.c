/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_graph_find_reverse.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 18:38:56 by jayache           #+#    #+#             */
/*   Updated: 2019/01/28 15:42:14 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

t_edge	*graph_find_reverse(t_node *a, t_node *b)
{
	t_edge	**edges;
	size_t	x;

	x = 0;
	edges = a->e;
	while (x < a->edges_number)
	{
		if (edges[x]->next == b)
			return (edges[x]);
		++x;
	}
	return (NULL);
}
