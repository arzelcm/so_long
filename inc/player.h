/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:32:36 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/06 14:09:15 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "position.h"
# include "image.h"

typedef struct s_player
{
	t_position		pos;
	size_t			collectibles;
	int				moving_up;
	int				moving_down;
	int				moving_left;
	int				moving_right;
	size_t			movements;
	size_t			movement_iterations;
	t_image			texture;
	unsigned int	acceleration;
}	t_player;

void	init_player(t_player *player);

void	update_player_movement(int key, t_player *player, int moving);

typedef struct s_map	t_map;

void	move_player(t_player *player, size_t x, size_t y, t_map *map);

#endif