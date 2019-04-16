/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_node_new.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 11:05:19 by jayache           #+#    #+#             */
/*   Updated: 2019/01/24 18:28:13 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

t_node			*ft_graph_node_new(t_info *i, size_t size)
{
	t_node		*n;

	if (!(n = (t_node*)ft_memalloc(sizeof(t_node))))
		exit(EXIT_FAILURE);
	n->size = size;
	n->i = i;
	n->ant_id = -1;
	if (!(n->e = ft_memalloc(sizeof(t_edge*))))
		exit(EXIT_FAILURE);
	n->edges_number = 0;
	return (n);
}
