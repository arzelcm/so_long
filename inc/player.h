/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 15:32:36 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/26 21:17:46 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

# include "position.h"
# include "texture.h"

typedef struct s_player
{
	t_position	pos;
	size_t		collectibles;
	int			moving_up;
	int			moving_down;
	int			moving_left;
	int			moving_right;
	size_t		movements;
	size_t		movement_iterations;
	t_texture	texture;
}	t_player;

void	init_player(t_player *player);

void	update_player_movement(int key, t_player *player, int moving);

#endif