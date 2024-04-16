/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:23:16 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/16 14:28:44 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H
# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

typedef struct s_position
{
	size_t	y;
	size_t	x;
}	t_position;

typedef struct s_player
{
	t_position	position;
	int			collectibles;
}	t_player;

typedef struct s_texture
{
	int		x_size;
	int		y_size;
	void	*img;
}	t_texture;

typedef struct s_map
{
	t_player	player;
	char		*path;
	char		*filename;
	char		*name;
	char		**spaces;
	char		*elems;
	t_texture	wall;
	t_texture	empty_space;
	t_position	position;
	size_t		max_y;
	size_t		max_x;
}	t_map;

typedef struct s_accessible_elems
{
	int			exit;
	int			collectibles;
}	t_elems;

void	terminate_map(t_map *map);

void	print_map(t_map *map);

#endif