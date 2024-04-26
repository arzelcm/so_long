/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/11 14:11:08 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/26 21:17:37 by arcanava         ###   ########.fr       */
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
	dst->player.pos.x = src->player.pos.x;
	dst->player.pos.y = src->player.pos.y;
}

void	terminate_map(t_map *map)
{
	free_matrix(map->spaces, map->max_y);
	if (map->elems)
		free(map->elems);
}

void game_over(t_player *player, t_map *map)
{
	if (player->collectibles == map->collectible_amount)
	{
		ft_printf("\033[1A\033[2KYEAH!!! YOU WON!\nMovements: %i\n\033[?25h", map->player.movements);
		exit(EXIT_SUCCESS);
	}
	else
		ft_printf("\a");
}

void	move_player(t_player *player, size_t x, size_t y, t_map *map)
{
	if (map->spaces[player->pos.y + y][player->pos.x + x] == WALL)
		return ;
	else if (map->spaces[player->pos.y + y][player->pos.x + x] == COLLECTIBLE)
	{
		player->collectibles++;
		map->spaces[player->pos.y + y][player->pos.x + x] = EMPTY;
	}
	else if (map->spaces[player->pos.y + y][player->pos.x + x] == EXIT)
	{
		game_over(player, map);
		return;
	}
	map->spaces[player->pos.y][player->pos.x] = EMPTY;
	player->pos.y += y;
	player->pos.x += x;
	player->movements++;
	map->spaces[player->pos.y][player->pos.x] = PLAYER;
	ft_printf("\033[1A\033[2KMovements: %i\n", player->movements);
}
