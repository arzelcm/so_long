/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:17:57 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/12 20:24:02 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "map.h"
#include "context.h"
#include "../lib/libft/libft.h"
#include "safe_utils.h"
#include "utils.h"
#include "so_long.h"

void	print_map(t_map *map)
{
	size_t	i;

	ft_printf("Opened map: %s\n", map->path);
	i = -1;
	while (++i < map->max_y)
		ft_printf("%s\n", map->spaces[i]);
	ft_printf("Elems: %s\n", map->elems);
	ft_printf("Player pos: (%i, %i)\n", map->player.position.i, map->player.position.j);
}

int	is_closed_map(t_map *map)
{
	size_t	i;
	size_t	j;
	int		closed;

	closed = 1;
	i = 0;
	while (map && i < map->max_y && closed)
	{
		j = 0;
		while (j < map->max_x && closed)
		{
			if (i == 0 || i == map->max_y - 1 || j == 0 || j == map->max_x - 1)
				closed = map->spaces[i][j] == WALL;
			j++;
		}
		i++;
	}
	return (closed);
}

void	find_accessible_elems(t_map *map, t_elems *elems, size_t i, size_t j)
{
	if (i < 0 || j < 0 || i >= map->max_y || j >= map->max_x
		|| map->spaces[i][j] == 'A' || map->spaces[i][j] == WALL)
		return ;
	else if (map->spaces[i][j] == EXIT)
		elems->exit++;
	else if (map->spaces[i][j] == COLLECTIBLE)
		elems->collectibles++;
	map->spaces[i][j] = 'A';
	find_accessible_elems(map, elems, i, j + 1);
	find_accessible_elems(map, elems, i, j - 1);
	find_accessible_elems(map, elems, i + 1, j);
	find_accessible_elems(map, elems, i - 1, j);
}

int	has_valid_path_map(t_context *context)
{
	t_elems	elems;
	t_map	accessible_map;

	elems.collectibles = 0;
	elems.exit = 0;
	find_accessible_elems(copy_map(&accessible_map, context),
		&elems, context->map.player.position.i, context->map.player.position.j);
	terminate_map(&accessible_map);
	ft_printf("collectibles: %i, exit: %i\n", elems.collectibles, elems.exit);
	return (elems.exit
		&& elems.collectibles == ft_stroccurrences(context->map.elems, COLLECTIBLE));
}

void	check_map(t_context *context)
{
	char	*message;

	print_map(&context->map);
	if (ft_stroccurrences(context->map.elems, PLAYER) != 1)
		message = ": map must have one starting position for player";
	else if (ft_stroccurrences(context->map.elems, EXIT) != 1)
		message = ": map must have one exit";
	else if (ft_stroccurrences(context->map.elems, COLLECTIBLE) < 1)
		message = ": map must have at least one collectible";
	else if (!is_closed_map(&context->map))
		message = ": map must be sorrounded by walls";
	else if (!has_valid_path_map(context))
		message = ": player must be able to exit the map";
	else
		return ;
	write(2, context->map.path, ft_strlen(context->map.path));
	custom_error(message, context);
}

void	push_elems(char *str, size_t i, t_context *context)
{
	size_t	j;
	char	elem;

	j = 0;
	while (str[j])
	{
		elem = str[j];
		if (elem != EMPTY && elem != WALL)
			push_char(str[j], &context->map.elems, context);
		if (elem == PLAYER)
		{
			context->map.player.position.i = i;
			context->map.player.position.j = j;
		}
		j++;
	}
}

void	set_map(char *path, t_context *context)
{
	char	*line;
	int		fd;
	int		correct;

	correct = 1;
	fd = safe_open(path, O_RDONLY, context);
	line = get_next_line(fd, 0);
	context->map.max_x = ft_strlen(line);
	while (line && correct)
	{
		if (context->map.max_x != ft_strlen(line))
			correct = 0;
		else
		{
			push_string(line, &context->map.spaces,
				context->map.max_y, context);
			push_elems(line, context->map.max_y, context);
			line = get_next_line(fd, 0);
		}
		context->map.max_y++;
	}
	safe_close(&fd, context);
	if (!correct)
		custom_error("map must be rectangular!", context);
}

void	check_extension(char *path, t_context *context)
{
	char	*filename;

	filename = ft_filename(path);
	if (ft_strlen(filename) <= 4
		|| ft_strnrcmp(filename, ".ber", 4) != EQUAL_STRINGS)
	{
		write(STDERR_FILENO, filename, ft_strlen(filename));
		custom_error(": invalid file extension, only .ber is allowed!",
			context);
	}
}

void	init_map(t_map *map, char *path, t_context *context)
{
	(void) context;
	map->path = path;
	map->spaces = NULL;
	map->elems = NULL;
	map->max_y = 0;
	map->max_x = 0;
}

void	handle_map(char **argv, t_context *context)
{
	check_extension(argv[1], context);
	init_map(&context->map, argv[1], context);
	set_map(argv[1], context);
	check_map(context);
	print_map(&context->map);
}
