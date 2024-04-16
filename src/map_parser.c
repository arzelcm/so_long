/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:39:11 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/16 20:26:33 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "utils.h"
#include "actuator.h"
#include "map.h"

void	init_texture(t_texture *texture, char *img_path, void *mlx)
{
	texture->x_size = 0;
	texture->y_size = 0;
	texture->img = mlx_xpm_file_to_image(mlx, img_path,
		&texture->x_size, &texture->y_size);
}

void	init_window(t_texture *wall, t_texture *empty_space,
			t_map *map, t_context *context)
{
	if (wall->x_size != wall->y_size || wall->x_size != empty_space->x_size || wall->y_size != empty_space->y_size)
		custom_error("Texture .xpm images must be square and have exactly the same size!",
			context);
	context->window.title = context->map.name;
	context->window.width = empty_space->x_size * map->max_x;
	context->window.height = empty_space->y_size * map->max_y;
	if (context->window.width > 1920)
		context->window.width = 1920;
	if (context->window.height > 1080)
		context->window.height = 1080;
	context->window.ref = mlx_new_window(context->mlx, context->window.width,
							context->window.height, map->name);
}

void	parse_map(t_map *map, t_context *context)
{
	size_t		x;
	size_t		y;
	int			x_factr;
	int			y_factr;
	size_t		initial_y;
	size_t		initial_x;

	// TODO: put exit, player and collectibles
	x_factr = map->empty_space.x_size;
	y_factr = map->empty_space.y_size;
	// ft_printf("Window width: %i, height: %i\n", context->window.width, context->window.height);
	// ft_printf("max_x: %i, max_y: %i\n", map->max_x, map->max_y);
	initial_y = ft_normalize(map->position.y, 0, map->max_y - context->window.height / y_factr);
	initial_x = ft_normalize(map->position.x, 0, map->max_x - context->window.width / x_factr);
	ft_printf("initial_x: %i, initial_y: %i\n", initial_x, initial_y);
	y = 0;
	// TODO: Remove ??
	mlx_clear_window(context->mlx, context->window.ref);
	while (y < map->max_y && y < (size_t) context->window.height / y_factr)
	{
		x = 0;
		while (x < map->max_x && x < (size_t) context->window.width / x_factr)
		{
			if (map->spaces[y + initial_y][x + initial_x] == EMPTY)
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->empty_space.img, x * x_factr, y * y_factr);
			else if (map->spaces[y + initial_y][x + initial_x] == WALL)
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->wall.img, x * x_factr, y * y_factr);
			x++;
		}
		y++;
	}
	// ft_printf("last_x: %i, last_y: %i\n", x, y);
	// print_map(map);
}

void	set_map_initial_pos(t_map *map, t_context *context)
{
	long	x_middle;
	long	y_middle;

	x_middle = context->window.width / 2 / map->wall.x_size;
	y_middle = context->window.height / 2 / map->wall.y_size;

	map->position.x = (long) map->player.position.x - x_middle;
	map->position.y = (long) map->player.position.y - y_middle;
}

void	use_map(t_map *map, t_context *context)
{
	init_texture(&map->wall, WALL_TEXTURE, context->mlx);
	init_texture(&map->empty_space, EMPTY_TEXTURE, context->mlx);
	init_window(&map->wall, &map->empty_space, map, context);
	set_map_initial_pos(map, context);
	parse_map(map, context);
	mlx_key_hook(context->window.ref, on_key_down, context);
	mlx_loop(context->mlx);
}