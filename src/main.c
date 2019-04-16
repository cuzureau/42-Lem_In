/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 11:28:01 by cuzureau          #+#    #+#             */
/*   Updated: 2019/01/29 16:51:37 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

void			ft_exit_clean(void)
{
	write(1, "ERROR\n", 6);
	exit(EXIT_FAILURE);
}

void			ft_check_posibility(t_lemin *l)
{
	t_node			*n;

	if (l->is_start == 0 || l->is_end == 0)
		ft_exit_clean();
	n = ft_graph_node_search_type(l->g, R_START);
	if (n->edges_number < 1)
		ft_exit_clean();
	n = ft_graph_node_search_type(l->g, R_END);
	if (n->edges_number < 1)
		ft_exit_clean();
}

static	void	print_parse(t_buffer *buf)
{
	size_t	i;

	i = 0;
	while (i < buf->size && buf->buffer[i])
	{
		ft_printf("%s\n", buf->buffer[i]);
		++i;
	}
	ft_printf("\n");
}

int				main(void)
{
	t_lemin		*l;
	int			best_bundle;
	int			flow;

	if (!(l = (t_lemin*)ft_memalloc(sizeof(t_lemin) + 20)))
		exit(EXIT_FAILURE);
	if (!(l->buff = (t_buffer*)ft_memalloc(sizeof(t_buffer))))
		exit(EXIT_FAILURE);
	ft_parse(l);
	if (!(flow = ft_init_algo(l)))
		ft_exit_clean();
	best_bundle = find_best_bundle(l);
	print_parse(l->buff);
	send_ants(l, l->bundles[best_bundle]);
	exit(EXIT_SUCCESS);
}
