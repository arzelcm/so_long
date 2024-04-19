/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 15:17:57 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/19 20:38:16 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "map.h"
#include "context.h"
#include "../lib/libft/libft.h"
#include "safe_utils.h"
#include "utils.h"
#include "so_long.h"
#include "player.h"

void	print_map(t_map *map)
{
	size_t	i;

	ft_printf("Opened map: %s\n", map->path);
	i = -1;
	while (++i < map->max_y)
		ft_printf("%s\n", map->spaces[i]);
	ft_printf("Elems: %s\n", map->elems);
	ft_printf("Player pos: (%i, %i)\n", map->player.position.y, map->player.position.x);
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
	if (map->spaces[i][j] == EXIT)
		elems->exit++;
	else if (map->spaces[i][j] == COLLECTIBLE)
		elems->collectibles++;
	map->spaces[i][j] = 'A';
	elems->iterations++;
	if (map->spaces[i][j + 1] != 'A' && map->spaces[i][j + 1] != WALL)
		find_accessible_elems(map, elems, i, j + 1);
	if (map->spaces[i][j - 1] != 'A' && map->spaces[i][j - 1] != WALL)
		find_accessible_elems(map, elems, i, j - 1);
	if (map->spaces[i + 1][j] != 'A' && map->spaces[i + 1][j] != WALL)
		find_accessible_elems(map, elems, i + 1, j);
	if (map->spaces[i - 1][j] != 'A' && map->spaces[i - 1][j] != WALL)
		find_accessible_elems(map, elems, i - 1, j);
}
void	find_accessible_elems_iter(t_map *map, t_elems *elems)
{
	t_pos_stack	*stack;

	stack = new_pos(map->player.position.x, map->player.position.y);
	while (stack)
	{
		if (map->spaces[stack->pos.y][stack->pos.x] == 'A' || map->spaces[stack->pos.y][stack->pos.x] == WALL)
		{
			shift_pos(&stack);
			continue ;
		}
		else if (map->spaces[stack->pos.y][stack->pos.x] == EXIT)
			elems->exit++;
		else if (map->spaces[stack->pos.y][stack->pos.x] == COLLECTIBLE)
			elems->collectibles++;
		map->spaces[stack->pos.y][stack->pos.x] = 'A';
		if (map->spaces[stack->pos.y][stack->pos.x + 1] != 'A'
				&& map->spaces[stack->pos.y][stack->pos.x + 1] != WALL)
			push_pos(stack, stack->pos.x + 1, stack->pos.y);
		if (map->spaces[stack->pos.y][stack->pos.x - 1] != 'A'
				&& map->spaces[stack->pos.y][stack->pos.x - 1] != WALL)
			push_pos(stack, stack->pos.x - 1, stack->pos.y);
		if (map->spaces[stack->pos.y + 1][stack->pos.x] != 'A'
				&& map->spaces[stack->pos.y + 1][stack->pos.x] != WALL)
			push_pos(stack, stack->pos.x, stack->pos.y + 1);
		if (map->spaces[stack->pos.y - 1][stack->pos.x] != 'A'
				&& map->spaces[stack->pos.y - 1][stack->pos.x] != WALL)
			push_pos(stack, stack->pos.x, stack->pos.y - 1);
		shift_pos(&stack);
		elems->iterations++;
	}
}

int	has_valid_path_map(t_map *map)
{
	t_elems	elems;
	t_map	accessible_map;
	size_t	stack_call_size;

	copy_map(&accessible_map, map);
	elems.collectibles = 0;
	elems.exit = 0;
	elems.iterations = 0;
	// TODO: Fix calculation
	stack_call_size = sizeof(&accessible_map) + sizeof(&elems) + sizeof(map->player.position.y)
		+ sizeof(map->player.position.x);
	ft_printf("x: %i, y: %i, walls: %i\n", map->max_x, map->max_y, map->walls_amount);
	if ((map->max_x * map->max_y - map->walls_amount) * stack_call_size + 500 > MAX_STACK_SIZE_KB * 1024 * 4){
		ft_printf("iter");find_accessible_elems_iter(&accessible_map, &elems);}
	else{
		ft_printf("recursive");find_accessible_elems(&accessible_map, &elems,
			map->player.position.y, map->player.position.x);}
	terminate_map(&accessible_map);
	exit(1);
	return (elems.exit &&
				elems.collectibles == ft_stroccurrences(map->elems, COLLECTIBLE));
}

void	check_map(t_context *context)
{
	char	*message = "a";

	message[0] = 'b';
	if (ft_stroccurrences(context->map.elems, PLAYER) != 1)
		message = ": map must have one starting position for player";
	else if (ft_stroccurrences(context->map.elems, EXIT) != 1)
		message = ": map must have one exit";
	else if (ft_stroccurrences(context->map.elems, COLLECTIBLE) < 1)
		message = ": map must have at least one collectible";
	else if (!is_closed_map(&context->map))
		message = ": map must be sorrounded by walls";
	else if (!has_valid_path_map(&context->map))
		message = ": player must be able to exit the map";
	else
		return ;
	write(2, "Error\n", 6);
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
		if (elem != WALL && elem != EMPTY && elem != PLAYER
			&& elem != EXIT && elem != COLLECTIBLE)
		{
			write(2, "Error\n", 6);
			write(2, context->map.filename, ft_strlen(context->map.filename));
			write(2, ": ", 2);
			write(2, &elem, 1);
			custom_error(" is not a valid map element. Only 1, 0, P, C and E are.",
				context);
		}
		else if (elem == PLAYER)
		{
			context->map.player.position.y = i;
			context->map.player.position.x = j;
		}
		else if (str[j] == WALL)
			context->map.walls_amount++;
		if (elem != EMPTY && elem != WALL)
			push_char(elem, &context->map.elems, context);
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
		write(2, "Error\n", 6);
	if (!correct)
		custom_error("map must be rectangular!", context);
}

void	check_extension(t_map *map, t_context *context)
{
	if (ft_strlen(map->filename) <= 4
		|| ft_strnrcmp(map->filename, ".ber", 4) != EQUAL_STRINGS)
	{
		write(2, "Error\n", 6);
		write(STDERR_FILENO, map->filename, ft_strlen(map->filename));
		custom_error(": invalid file extension, only .ber is allowed!",
			context);
	}
}

void	init_map(t_map *map, char *path, t_context *context)
{
	(void) context;
	map->spaces = NULL;
	map->elems = NULL;
	map->max_y = 0;
	map->max_x = 0;
	map->walls_amount = 0;
	map->path = path;
	map->filename = ft_filename(path);
	map->name = ft_substr(map->filename, 0, ft_strlen(map->filename) - 4);
	map->position.y = 0;
	map->position.x = 0;
	init_player(&map->player);
}

void	handle_map(char **argv, t_context *context)
{
	init_map(&context->map, argv[1], context);
	check_extension(&context->map, context);
	set_map(argv[1], context);
	check_map(context);
	// print_map(&context->map);
}
