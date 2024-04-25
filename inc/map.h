/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:23:16 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/25 20:35:31 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'

# include "stddef.h"
# include "position.h"
# include "player.h"
# include "texture.h"
#include <sys/stat.h>

typedef struct s_lposition
{
	long	y;
	long	x;
}	t_lposition;

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
	t_texture	collectible;
	t_texture	exit;
	t_lposition	position;
	size_t		max_y;
	size_t		max_x;
	size_t		walls_amount;
	size_t		collectible_amount;
	off_t		size;
	int			exit_amount;
	int			player_amount;
}	t_map;

typedef struct s_accessible_elems
{
	int			exit;
	size_t		collectibles;
	size_t		iterations;
}	t_elems;

void		handle_map(char **argv, t_map *map);

void		terminate_map(t_map *map);

void		print_map(t_map *map);

void		copy_map(t_map *dst, t_map *src);

#endif