/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_graph.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/30 10:53:49 by jayache           #+#    #+#             */
/*   Updated: 2019/01/24 18:27:59 by jayache          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

t_graph			*ft_graph_new(void)
{
	t_graph		*g;

	if (!(g = (t_graph*)ft_memalloc(sizeof(t_graph) + 1)))
		exit(EXIT_FAILURE);
	g->size = 0;
	if (!(g->n = (t_node**)ft_memalloc(sizeof(t_node*))))
		exit(EXIT_FAILURE);
	return (g);
}
