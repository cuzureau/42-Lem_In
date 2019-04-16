/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cuzureau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/01 11:09:42 by cuzureau          #+#    #+#             */
/*   Updated: 2019/02/05 11:45:28 by cuzureau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H

# define R_NORMAL 0
# define R_START 1
# define R_END 2

# include "../lib/inc/libft.h"

typedef struct		s_buffer
{
	char			**buffer;
	size_t			pos;
	size_t			size;
}					t_buffer;

typedef struct		s_info
{
	char			*name;
	unsigned char	status;
	int				x;
	int				y;
}					t_info;

typedef struct		s_edge
{
	struct s_edge	*prevv;
	int				flow;
	int				maxflow;
	int				added;
	int				visited;
	void			*prev;
	void			*next;
}					t_edge;

typedef struct		s_node
{
	t_info			*i;
	size_t			size;
	t_edge			**e;
	int				ant_id;
	size_t			edges_number;
}					t_node;

typedef struct		s_graph
{
	size_t			size;
	t_node			**n;
}					t_graph;

typedef struct		s_path
{
	t_node			**path;
	size_t			size;
}					t_path;

typedef struct		s_pathbundle
{
	t_path			*bundle;
	size_t			size;
	int				e_size;
	int				*to_send;
}					t_pathbundle;

typedef struct		s_lemin
{
	char			*line;
	t_buffer		*buff;
	t_edge			**path;
	t_graph			*g;
	t_pathbundle	**bundles;
	int				current_ant;
	int				*end_ants;
	unsigned char	is_start;
	unsigned char	is_end;
	int				total_paths;
	int				total_ants;
	int				total_tubes;
	int				total_rooms;
	int				total_bundle;
}					t_lemin;

/*
**	parse.c
*/

int					ft_parse_infos(t_lemin *l);
int					ft_parse_ants(t_lemin *l);
int					ft_parse_tubes(t_lemin *l);
t_info				*ft_parse_rooms(t_lemin *l);
void				ft_parse(t_lemin *l);

/*
**	tools.c
*/

unsigned char		ft_len_tab(char **tab, size_t num);
int					ft_strchr_num(char *str, char c);
void				ft_free_tab(char **tab, int size);
void				ft_check_posibility(t_lemin *l);
void				int_memset(int *ptr, int val, int size);
void				ft_fill_node(t_lemin *l, t_info *i, char **tab);

int					ft_init_algo(t_lemin *l);
void				ft_exit_clean();
int					main(void);

t_graph				*ft_graph_new(void);
t_node				*ft_graph_node_new(t_info *i, size_t size);
t_node				*ft_graph_node_search(t_graph *g, char *name);
t_node				*ft_graph_node_search_type(t_graph *g, unsigned char infos);
t_edge				*graph_find_reverse(t_node *a, t_node *b);
int					ft_graph_add_link(t_node *a, t_node *b);
int					ft_graph_add_node(t_graph *g, t_node *b);
t_edge				*ft_graph_edge_new(t_node *a, t_node *b);
void				search_path(t_lemin *l);

/*
** algo
*/

int					activate_way(t_lemin *l, t_edge *end, t_node *start,
					t_edge **pile);
int					filter(t_edge *edge, t_node *node, size_t size);
void				addbundle(t_lemin *l, int maxflow);
int					bfs(t_lemin *l, t_node *start);

/*
** bundles
*/

int					get_longest_path(t_path *paths, int size);
int					find_best_bundle(t_lemin *l);

/*
** sender
*/

void				send_ants(t_lemin *l, t_pathbundle *bundle);
void				buffer_add_lign(t_buffer *buff, char *lign);
#endif
