/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:35:59 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/06 14:14:21 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "player.h"
#include "map.h"
#include "libft.h"

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

void	check_game_over(t_player *player, t_map *map, char tile)
{
	if (tile == EXIT && player->collectibles == map->collectible_amount)
	{
		player->movements++;
		ft_printf("\033[1A\033[2KYEAH!!! YOU WON! :)\n");
		ft_printf("Movements: %l\n\033[?25h", map->player.movements);
		exit(EXIT_SUCCESS);
	}
	else if (tile == ENEMY)
	{
		player->movements++;
		ft_printf("\033[1A\033[2KYOU LOST! :(\n\033[?25h");
		exit(EXIT_SUCCESS);
	}
	else
		ft_printf("\a");
}

int	check_collitions(t_map *map, char tile)
{
	if (tile == WALL)
	{
		map->player.acceleration = 0;
		return (0);
	}
	else if (tile == COLLECTIBLE)
	{
		map->player.acceleration = 0;
		map->player.collectibles++;
		tile = EMPTY;
	}
	else if (tile == ENEMY)
	{
		check_game_over(&map->player, map, tile);
		return (0);
	}
	else if (tile == EXIT)
	{
		check_game_over(&map->player, map, tile);
		return (0);
	}
	return (1);
}

void	move_player(t_player *player, size_t x, size_t y, t_map *map)
{
	if (!check_collitions(map,
			map->spaces[player->pos.y + y][player->pos.x + x]))
		return ;
	map->spaces[player->pos.y][player->pos.x] = EMPTY;
	player->pos.y += y;
	player->pos.x += x;
	player->movements++;
	map->spaces[player->pos.y][player->pos.x] = PLAYER;
	player->acceleration += 300 + 200 / (player->acceleration + 1);
	ft_printf("\033[1A\033[2KMovements: %l\n", player->movements);
}
