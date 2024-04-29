/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:35:59 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/29 13:19:21 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "player.h"

void	init_player(t_player *player)
{
	player->pos.x = 0;
	player->pos.y = 0;
	player->collectibles = 0;
	player->movements = 0;
	player->moving_up = 0;
	player->moving_down = 0;
	player->moving_left = 0;
	player->moving_right = 0;
	player->movement_iterations = 0;
	player->acceleration = 0;
}

void	update_player_movement(int key, t_player *player, int moving)
{

	if (moving == 1)
	{
		player->movement_iterations = 0;
		player->acceleration = 0;
	}
	if (key == UP_KEYCODE || key == K_KEYCODE || key == W_KEYCODE)
		player->moving_up += moving;
	else if (key == DOWN_KEYCODE || key == J_KEYCODE || key == S_KEYCODE)
		player->moving_down += moving;
	else if (key == LEFT_KEYCODE || key == H_KEYCODE || key == A_KEYCODE)
		player->moving_left += moving;
	else if (key == RIGHT_KEYCODE || key == L_KEYCODE || key == D_KEYCODE)
		player->moving_right += moving;
}
