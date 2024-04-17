/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actuator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:53:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/17 12:57:22 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	move_map_position(long x_increment, long y_increment, t_map *map)
{
	map->position.x += x_increment;
	map->position.y += y_increment;
}
void game_over(t_context *context)
{
	// TODO: Check if is needed to terminate something!
	// close_map();
	if (context->map.player.collectibles == ft_stroccurrences(context->map.elems, COLLECTIBLE))
	{
		ft_printf("YEAH!!! YOU WON!\n");
		exit(EXIT_SUCCESS);
	}
	ft_printf("You lost :(\nCollectibles collected: %i/%i\n", context->map.player.collectibles, ft_stroccurrences(context->map.elems, COLLECTIBLE));
	exit(EXIT_FAILURE);
}

void	move_player(t_player *player, size_t x, size_t y, t_context *context)
{
	if (context->map.spaces[y][x] == WALL)
		return ;
	else if (context->map.spaces[y][x] == EXIT)
		game_over(context);
	else if (context->map.spaces[y][x] == COLLECTIBLE)
	{
		player->collectibles++;
		context->map.spaces[y][x] = EMPTY;
		ft_printf("Collectibles amount: %i\n", player->collectibles);
	}
	context->map.spaces[player->position.y][player->position.x] = EMPTY;
	player->position.y = y;
	player->position.x = x;
	context->map.spaces[y][x] = PLAYER;
}

void	move(int key, t_context *context)
{
	t_position pos;

	pos = context->map.player.position;
	if (key == UP_KEYCODE)
		move_player(&context->map.player, context->map.player.position.x,
			context->map.player.position.y - 1, context);
	else if (key == DOWN_KEYCODE)
		move_player(&context->map.player, context->map.player.position.x,
			context->map.player.position.y + 1, context);
	else if (key == LEFT_KEYCODE)
		move_player(&context->map.player, context->map.player.position.x - 1,
			context->map.player.position.y, context);
	else if (key == RIGHT_KEYCODE)
		move_player(&context->map.player, context->map.player.position.x + 1,
			context->map.player.position.y, context);
	if (pos.y != context->map.player.position.y || pos.x != context->map.player.position.x )
	{
		move_map_position(context->map.player.position.x - pos.x,
			context->map.player.position.y - pos.y, &context->map);
		parse_map(&context->map, context);
	}
}

int	on_key_down(int key, t_context *context)
{
	// ft_printf("Key pressed: %i\n", key);
	if (key == ESC_KEYCODE)
	{
		mlx_destroy_window(context->mlx, context->window.ref);
		exit(EXIT_SUCCESS);
	}
	else if (key <= 126 && key >= 123)
		move(key, context);
	return (0);
}