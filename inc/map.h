/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:23:16 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 19:22:06 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_H
# define MAP_H

# define EMPTY '0'
# define WALL '1'
# define COLLECTIBLE 'C'
# define EXIT 'E'
# define PLAYER 'P'
# define ENEMY 'M'

# include "stddef.h"
# include "position.h"
# include "player.h"
# include "image.h"
# include "position_stack.h"
# include "sprite.h"
# include <sys/stat.h>
# include <pthread.h>

typedef struct s_map
{
	t_player	player;
	char		*path;
	char		*filename;
	char		*name;
	char		**spaces;
	char		*elems;
	t_sprite	*wall;
	t_image		empty_space;
	t_image		collectible;
	t_image		exit;
	t_image		enemy;
	t_lposition	position;
	size_t		max_y;
	size_t		max_x;
	size_t		walls_amount;
	size_t		collectible_amount;
	off_t		size;
	int			exit_amount;
	int			player_amount;
	int			checked;
}	t_map;

typedef struct s_accessible_elems
{
	int			exit;
	size_t		collectibles;
	size_t		iterations;
}	t_elems;

typedef struct s_checking_status
{
	t_map			map;
	t_elems			elems;
	t_pos_stack		**stack;
	pthread_mutex_t	checked_mutex;
	pthread_mutex_t	iteration_mutex;
}	t_checking_status;

void		handle_map(char **argv, t_map *map);

void		terminate_map(t_map *map);

void		print_map(t_map *map);

void		copy_map(t_map *dst, t_map *src);

void		move_player(t_player *player, size_t x, size_t y, t_map *map);

#endif