/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:17:57 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/06 15:45:15 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "safe_utils.h"
#include "utils.h"
#include "loader.h"
#include "position_stack.h"
#include "map.h"

void	print_map(t_map *map)
{
	size_t	i;

	ft_printf("Opened map: %s\n", map->path);
	i = -1;
	while (++i < map->max_y)
		ft_printf("%s\n", map->spaces[i]);
	ft_printf("Player pos: (%i, %i)\n",
		map->player.pos.y, map->player.pos.x);
	ft_printf("players: %i, exits: %i, collectibles: %i, walls: %i\n",
		map->player_amount, map->exit_amount,
		map->collectible_amount, map->walls_amount);
}

void	increment_elems(char elem, t_map *map, size_t i, size_t j)
{
	if (elem == PLAYER)
	{
		map->player_amount++;
		map->player.pos.y = i;
		map->player.pos.x = j;
	}
	else if (elem == WALL)
		map->walls_amount++;
	else if (elem == EXIT)
		map->exit_amount++;
	else if (elem == COLLECTIBLE)
		map->collectible_amount++;
}

void	find_elems(char *str, size_t i, t_map *map)
{
	size_t	j;

	j = -1;
	while (str[++j])
	{
		if (str[j] != WALL && str[j] != EMPTY && str[j] != PLAYER
			&& str[j] != EXIT && str[j] != COLLECTIBLE && str[j] != ENEMY)
		{
			ft_printff(STDERR_FILENO,
				"\033[1A\033[2KError\nin %s, %c: is not a valid map element. ",
				map->filename, str[j]);
			custom_error("Only 1, 0, P, C, M and E are.");
		}
		increment_elems(str[j], map, i, j);
	}
}

void	load_map(char *path, t_map *map)
{
	char	*line;
	int		fd;

	update_loading("Loading map", 0);
	fd = safe_open(path, O_RDONLY);
	set_map_size(map, fd);
	line = get_next_line(fd, 0);
	map->max_x = ft_strlen(line);
	while (line)
	{
		if (map->max_x != ft_strlen(line))
		{
			ft_printff(STDERR_FILENO, "\033[1A\033[2KError\n");
			custom_error("map must be rectangular!");
		}
		push_string(line, &map->spaces, map->max_y);
		find_elems(line, map->max_y, map);
		line = get_next_line(fd, 0);
		if (map->max_y % 100 == 0)
			update_loading("Loading map",
				map->max_y * map->max_x * sizeof(char) * 100 / map->size);
		map->max_y++;
	}
	safe_close(&fd);
	update_loading("Loading map", 100);
}

void	set_map(char *path, t_map *map)
{
	map->spaces = NULL;
	map->max_y = 0;
	map->max_x = 0;
	map->walls_amount = 0;
	map->collectible_amount = 0;
	map->exit_amount = 0;
	map->player_amount = 0;
	map->path = path;
	map->filename = ft_filename(path);
	if (ft_strlen(map->filename) <= 4
		|| ft_strnrcmp(map->filename, ".ber", 4) != EQUAL_STRINGS)
	{
		ft_printff(STDERR_FILENO, "\033[1A\033[2KError\n%s: ", map->filename);
		custom_error("invalid file extension, only .ber is allowed!");
	}
	map->name = ft_substr(map->filename, 0, ft_strlen(map->filename) - 4);
	map->position.y = 0;
	map->position.x = 0;
	map->checked = 0;
	init_player(&map->player);
	load_map(path, map);
	check_map(map);
}
