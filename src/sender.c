/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/19 17:27:28 by jayache           #+#    #+#             */
/*   Updated: 2019/02/18 16:05:42 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

/*
** SIMULATE ONE STEP FOR ONE PATH
*/

static int		update_path(t_lemin *l, t_pathbundle *bundle, int index, int t)
{
	unsigned long	i;
	int				code;

	code = 0;
	i = bundle->bundle[index].size - 1;
	bundle->bundle[index].path[i]->ant_id = -1;
	while (i > 0)
	{
		if (bundle->bundle[index].path[i - 1]->ant_id != -1)
			code = 1;
		bundle->bundle[index].path[i]->ant_id =
			bundle->bundle[index].path[i - 1]->ant_id;
		if (i == bundle->bundle[index].size - 1)
			l->end_ants[index] = bundle->bundle[index].path[i]->ant_id;
		--i;
	}
	bundle->bundle[index].path[0]->ant_id = -1;
	if (bundle->bundle[index].path[0]->ant_id == -1 && l->current_ant <
			l->total_ants + 1 && bundle->to_send[index] > t)
	{
		bundle->bundle[index].path[0]->ant_id = l->current_ant;
		code = 2;
	}
	return (code);
}

static int		print_name(int id, char *name, int space)
{
	if (space)
		ft_printf(" ");
	ft_printf("L%d-%s", id, name);
	return (1);
}

static void		print_solution(t_path *paths, int total_path, int max_path,
				int *end_ants)
{
	int i;
	int	pos;
	int space;

	space = 0;
	pos = 1;
	while (pos <= max_path)
	{
		i = 0;
		while (i < total_path)
		{
			if (pos == 1 && end_ants[i] != -1)
				space = print_name(end_ants[i],
					paths[i].path[paths[i].size - pos]->i->name, space);
			else if (((int)paths[i].size - pos) >= 0 \
					&& paths[i].path[paths[i].size - pos]->ant_id != -1)
				space = print_name(paths[i].path[paths[i].size - pos]->ant_id,
						paths[i].path[paths[i].size - pos]->i->name, space);
			++i;
		}
		++pos;
	}
	ft_printf("\n");
}

static int		update_all(t_lemin *l, t_pathbundle *bundle, int nblign)
{
	int	i;
	int	progress;
	int	code;

	progress = 0;
	i = 0;
	while (i < bundle->e_size)
	{
		code = update_path(l, bundle, i, nblign);
		if (code >= 2)
			l->current_ant += 1;
		++i;
		if (code >= 1)
		{
			progress = 1;
		}
	}
	return (progress);
}

void			send_ants(t_lemin *l, t_pathbundle *bundle)
{
	int i;
	int	code;
	int maxsize;
	int	nblign;

	maxsize = get_longest_path(bundle->bundle, bundle->e_size);
	code = 1;
	if (!(l->end_ants = (int*)ft_memalloc(sizeof(int) * l->total_paths)))
		exit(EXIT_FAILURE);
	int_memset(l->end_ants, -1, l->total_paths);
	l->current_ant = 1;
	nblign = 0;
	while (code)
	{
		i = 0;
		code = update_all(l, bundle, nblign);
		if (code)
		{
			print_solution(bundle->bundle, bundle->e_size, maxsize,
			l->end_ants);
			nblign++;
		}
	}
}
