/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:11:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 18:08:16 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "context.h"
#include "utils.h"
#include "safe_utils.h"

void	copy_map(t_map *dst, t_map *src)
{
	size_t	i;

	dst->spaces = safe_malloc(sizeof(char *) * src->max_y);
	i = -1;
	while (++i < src->max_y)
		dst->spaces[i] = ft_strdup(src->spaces[i]);
	dst->elems = NULL;
	dst->max_x = src->max_x;
	dst->max_y = src->max_y;
	dst->walls_amount = src->walls_amount;
	dst->collectible_amount = src->collectible_amount;
	dst->player.pos.x = src->player.pos.x;
	dst->player.pos.y = src->player.pos.y;
}

void	terminate_map(t_map *map)
{
	free_matrix(map->spaces, map->max_y);
	if (map->elems)
		free(map->elems);
}

void	check_game_over(t_player *player, t_map *map, char tile)
{
	if (tile == EXIT && player->collectibles == map->collectible_amount)
	{
		ft_printf("\033[1A\033[2KYEAH!!! YOU WON! :)\n");
		ft_printf("Movements: %l\n\033[?25h", map->player.movements);
		exit(EXIT_SUCCESS);
	}
	else if (tile == ENEMY)
	{
		ft_printf("\033[1A\033[2KYOU LOST! :(\n\033[?25h");
		exit(EXIT_SUCCESS);
	}
	else
		ft_printf("\a");
}

// TODO: tile should be an enum!!!
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
