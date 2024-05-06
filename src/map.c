/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:17:57 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/06 11:31:09 by arcanava         ###   ########.fr       */
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
	ft_printf("Elems: %s\n", map->elems);
	ft_printf("Player pos: (%i, %i)\n",
		map->player.pos.y, map->player.pos.x);
	ft_printf("players: %i, exits: %i, collectibles: %i, walls: %i\n",
		map->player_amount, map->exit_amount,
		map->collectible_amount, map->walls_amount);
}



void	push_elems(char *str, size_t i, t_map *map)
{
	size_t	j;
	char	elem;

	j = 0;
	while (str[j])
	{
		elem = str[j];
		if (elem != WALL && elem != EMPTY && elem != PLAYER
			&& elem != EXIT && elem != COLLECTIBLE && elem != ENEMY)
		{
			ft_printff(STDERR_FILENO,
				"\033[1A\033[2KError\nin %s, %c: is not a valid map element. ",
				map->filename, elem);
			custom_error("Only 1, 0, P, C, M and E are.");
		}
		else if (elem == PLAYER)
		{
			map->player_amount++;
			map->player.pos.y = i;
			map->player.pos.x = j;
		}
		else if (str[j] == WALL)
			map->walls_amount++;
		else if (str[j] == EXIT)
			map->exit_amount++;
		else if (str[j] == COLLECTIBLE)
			map->collectible_amount++;
		if (elem != EMPTY && elem != WALL)
			push_char(elem, &map->elems);
		j++;
	}
}

void	load_map_size(t_map *map, int fd)
{
	struct stat	stat;

	fstat(fd, &stat);
	map->size = stat.st_size;
}

void	load_map(char *path, t_map *map)
{
	char	*line;
	int		fd;
	int		correct;
	size_t	i;

	update_loading("Loading map", 0);
	correct = 1;
	fd = safe_open(path, O_RDONLY);
	load_map_size(map, fd);
	i = 1;
	line = get_next_line(fd, 0);
	map->max_x = ft_strlen(line);
	while (line && correct)
	{
		if (map->max_x != ft_strlen(line))
			correct = 0;
		else
		{
			push_string(line, &map->spaces,
				map->max_y);
			push_elems(line, map->max_y, map);
			line = get_next_line(fd, 0);
		}
		map->max_y++;
		i++;
		if (i % 100 == 0)
			update_loading("Loading map",
				i * map->max_x * sizeof(char) * 100 / map->size);
	}
	safe_close(&fd);
	if (!correct)
	{
		ft_printff(STDERR_FILENO, "\033[1A\033[2KError\n");
		custom_error("map must be rectangular!");
	}
	update_loading("Loading map", 100);
}

void	set_map(char *path, t_map *map)
{
	map->spaces = NULL;
	map->elems = NULL;
	map->max_y = 0;
	map->max_x = 0;
	map->walls_amount = 0;
	map->collectible_amount = 0;
	map->exit_amount = 0;
	map->player_amount = 0;
	map->path = path;
	map->filename = ft_filename(path);
	check_extension(map);
	map->name = ft_substr(map->filename, 0, ft_strlen(map->filename) - 4);
	map->position.y = 0;
	map->position.x = 0;
	map->checked = 0;
	init_player(&map->player);
	load_map(path, map);
	check_map(map);
}
