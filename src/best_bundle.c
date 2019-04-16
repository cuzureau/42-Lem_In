/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   best_bundle.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jayache <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/20 17:31:19 by jayache           #+#    #+#             */
/*   Updated: 2019/02/18 16:07:44 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/lemin.h"

static int	calc_time(int a, int b, t_pathbundle *bundle)
{
	bundle->e_size = b;
	if (a % b == 0)
		return (a / b);
	else
		return ((a / b) + 1);
}

int			get_longest_path(t_path *paths, int size)
{
	int		i;
	size_t	max;

	max = 0;
	i = 0;
	while (i < size)
	{
		max = paths[i].size > max ? paths[i].size : max;
		++i;
	}
	return (max);
}

static int	simulate(t_pathbundle *bundle, int nb_ants)
{
	size_t	i;
	int		used;
	int		way;
	int		time;

	way = 1;
	i = 0;
	time = bundle->bundle[0].size + nb_ants;
	if (bundle->size == 1)
		return (calc_time(time, 1, bundle));
	used = bundle->bundle[1].size - bundle->bundle[0].size;
	while (i < bundle->size - 1 && used < nb_ants)
	{
		if (bundle->bundle[i].size + ((nb_ants - used) * way) >
				bundle->bundle[i + 1].size && way < nb_ants)
		{
			time += bundle->bundle[i + 1].size;
			way++;
			used += (bundle->bundle[i + 1].size - bundle->bundle[i].size) * way;
		}
		else
			return (calc_time(time, way, bundle));
		++i;
	}
	return (calc_time(time, way, bundle));
}

static void	calc_best_distrib(t_pathbundle *bundle, int nb_ants)
{
	size_t	i;
	size_t	tmp;

	tmp = 0;
	i = 0;
	if (!(bundle->to_send = (int*)ft_memalloc(sizeof(int) \
				* (size_t)bundle->size)))
		exit(EXIT_FAILURE);
	while (nb_ants > 0)
	{
		tmp++;
		i = 0;
		while (i < bundle->size)
		{
			if (bundle->bundle[i].size < tmp && nb_ants > 0)
			{
				bundle->to_send[i] += 1;
				nb_ants--;
			}
			++i;
		}
	}
}

int			find_best_bundle(t_lemin *l)
{
	int	i;
	int	best;
	int	best_index;
	int	tmp;

	i = 0;
	best = INT_MAX;
	best_index = 0;
	while (i < l->total_bundle)
	{
		tmp = simulate(l->bundles[i], l->total_ants);
		calc_best_distrib(l->bundles[i], l->total_ants);
		tmp = l->bundles[i]->to_send[0] + l->bundles[i]->bundle[0].size - 1;
		if (tmp <= best)
		{
			best = tmp;
			best_index = i;
		}
		++i;
	}
	return (best_index);
}
