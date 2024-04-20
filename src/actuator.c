/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actuator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:53:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/20 14:22:06 by arcanava         ###   ########.fr       */
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
		ft_printf("\033[2KYEAH!!! YOU WON!\nMovements: %i\n", context->map.player.movements);
		exit(EXIT_SUCCESS);
	}
	ft_printf("\033[2KYou lost :(\nCollectibles collected: %i/%i\nMovements: %i\n", context->map.player.collectibles, ft_stroccurrences(context->map.elems, COLLECTIBLE), context->map.player.movements);
	exit(EXIT_FAILURE);
}

void	move_player(t_player *player, size_t x, size_t y, t_context *context)
{
	player->moving = 1;
	while (player->moving
			&& context->map.spaces[player->pos.y + y][player->pos.x + x] != WALL)
	{
		player->moving = 0;
		if (context->map.spaces[player->pos.y + y][player->pos.x + x] == WALL)
			return ;
		else if (context->map.spaces[player->pos.y + y][player->pos.x + x] == COLLECTIBLE)
		{
			player->collectibles++;
			context->map.spaces[player->pos.y + y][player->pos.x + x] = EMPTY;
			// ft_printf("Collectibles amount: %i\n", player->collectibles);
		}
		context->map.spaces[player->pos.y][player->pos.x] = EMPTY;
		player->pos.y += y;
		player->pos.x += x;
		player->movements++;
		if (context->map.spaces[player->pos.y][player->pos.x] == EXIT)
			game_over(context);
		context->map.spaces[player->pos.y][player->pos.x] = PLAYER;
		ft_printf("Movements: %i\n\033[1F", player->movements);
		// usleep(1000000);
		// ft_printf("(%i, %i), Movements: %i\n", player->pos.y, player->pos.x, player->movements);
	}
	player->moving = 0;
}

void	move(int key, t_context *context)
{
	t_position pos;

	pos = context->map.player.pos;
	if (key == UP_KEYCODE || key == K_KEYCODE || key == W_KEYCODE)
		move_player(&context->map.player, 0, -1, context);
	else if (key == DOWN_KEYCODE || key == J_KEYCODE || key == S_KEYCODE)
		move_player(&context->map.player, 0, 1, context);
	else if (key == LEFT_KEYCODE || key == H_KEYCODE || key == A_KEYCODE)
		move_player(&context->map.player, -1, 0, context);
	else if (key == RIGHT_KEYCODE || key == L_KEYCODE || key == D_KEYCODE)
		move_player(&context->map.player, 1, 0, context);
	if (pos.y != context->map.player.pos.y || pos.x != context->map.player.pos.x )
	{
		move_map_position(context->map.player.pos.x - pos.x,
			context->map.player.pos.y - pos.y, &context->map);
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
	move(key, context);
	return (1);
}

int	on_key_up(int key, t_context *context)
{
	(void) context;
	(void) key;
	// ft_printf("Key released: %i\n", key);
	// if (key == ESC_KEYCODE)
	// {
	// 	mlx_destroy_window(context->mlx, context->window.ref);
	// 	exit(EXIT_SUCCESS);
	// }
	// move(key, context);
	return (1);
}