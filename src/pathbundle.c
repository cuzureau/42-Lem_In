/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathbundle.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 15:01:06 by jayache           #+#    #+#             */
/*   Updated: 2019/02/18 15:42:35 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

static int				transform_path(t_path *path, int b, t_node *start,
						int level)
{
	size_t		i;

	i = 0;
	while (i < start->edges_number)
	{
		if (start->e[i]->flow > 0)
		{
			if (!transform_path(path, b, start->e[i]->next, level + 1))
				exit(EXIT_FAILURE);
			break ;
		}
		++i;
	}
	if (path[b].path == NULL)
	{
		path[b].size = level + 1;
		if (!(path[b].path = ft_memalloc(sizeof(t_node*) * (level + 2))))
			exit(EXIT_FAILURE);
	}
	path[b].path[level] = start;
	return (1);
}

static void				sort_path(t_path *path, int size)
{
	int		sorted;
	int		pos;
	t_path	tmp;

	sorted = 0;
	while (!sorted)
	{
		pos = 1;
		sorted = 1;
		while (pos < size)
		{
			if (path[pos].size != 0 && path[pos - 1].size != 0 \
					&& path[pos - 1].size > path[pos].size)
			{
				tmp = path[pos - 1];
				path[pos - 1] = path[pos];
				path[pos] = tmp;
				sorted = 0;
			}
			pos++;
		}
	}
}

static t_path			*transform_into_path(t_lemin *l, t_node *start)
{
	size_t		i;
	t_path		*path;
	int			b;

	l->total_paths = start->edges_number;
	if (!(path = ft_memalloc(sizeof(t_path) * (start->edges_number + 2))))
		exit(EXIT_FAILURE);
	i = 0;
	b = 0;
	while (i < start->edges_number)
	{
		if (start->e[i]->flow > 0)
		{
			transform_path(path, b, start->e[i]->next, 0);
			++b;
		}
		++i;
	}
	sort_path(path, b);
	return (path);
}

static t_pathbundle		*create_bundle(t_lemin *l, int size)
{
	t_node			*start;
	t_pathbundle	*bundle;

	if (!(bundle = (t_pathbundle*)ft_memalloc(sizeof(t_pathbundle))))
		exit(EXIT_FAILURE);
	start = ft_graph_node_search_type(l->g, R_START);
	bundle->bundle = transform_into_path(l, start);
	bundle->size = size;
	return (bundle);
}

void					addbundle(t_lemin *l, int nb)
{
	t_pathbundle	**tmp;
	int				i;

	i = 0;
	if (!(tmp = ft_memalloc(sizeof(t_pathbundle*) * (l->total_bundle + 2))))
		exit(EXIT_FAILURE);
	while (i < l->total_bundle)
	{
		tmp[i] = l->bundles[i];
		++i;
	}
	tmp[i] = create_bundle(l, nb);
	if (l->bundles)
		free(l->bundles);
	l->bundles = tmp;
	l->total_bundle++;
}
