/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:39:11 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/24 18:52:23 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "actuator.h"
#include "loader.h"
#include "mlx.h"
#include "libft.h"
#include "window.h"

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
		custom_error("Texture .xpm images must be square and have exactly the same size!");
	context->window.title = context->map.name;
	context->window.width = empty_space->x_size * map->max_x;
	context->window.height = empty_space->y_size * map->max_y;
	if (context->window.width > WINDOW_MAX_WIDTH)
		context->window.width = ft_closest_multiple(WINDOW_MAX_WIDTH, wall->x_size);
	if (context->window.height > WINDOW_MAX_HEIGHT)
		context->window.height = ft_closest_multiple(WINDOW_MAX_HEIGHT, wall->y_size);
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
	// ft_printf("initial_x: %i, initial_y: %i\n", initial_x, initial_y);
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
			else if (map->spaces[y + initial_y][x + initial_x] == EXIT)
			{
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->empty_space.img, x * x_factr, y * y_factr);
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->exit.img, x * x_factr, y * y_factr);
			}
			else if (map->spaces[y + initial_y][x + initial_x] == COLLECTIBLE)
			{
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->empty_space.img, x * x_factr, y * y_factr);
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->collectible.img, x * x_factr, y * y_factr);
			}
			else if (map->spaces[y + initial_y][x + initial_x] == PLAYER)
			{
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->empty_space.img, x * x_factr, y * y_factr);
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->player.texture.img, x * x_factr, y * y_factr);
			}
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

	map->position.x = (long) map->player.pos.x - x_middle;
	map->position.y = (long) map->player.pos.y - y_middle;
}

void	use_map(t_map *map, t_context *context)
{
	update_loading("Building map", 0);
	init_texture(&map->wall, "./assets/textures/wall.xpm", context->mlx);
	init_texture(&map->empty_space, "./assets/textures/empty-space.xpm", context->mlx);
	init_texture(&map->collectible, "./assets/sprites/fish.xpm", context->mlx);
	init_texture(&map->exit, "./assets/sprites/bed.xpm", context->mlx);
	init_texture(&map->player.texture, "./assets/sprites/nuu-i-pussi.xpm", context->mlx);
	update_loading("Building map", 100);
	init_window(&map->wall, &map->empty_space, map, context);
	set_map_initial_pos(map, context);
	parse_map(map, context);
	// mlx_do_key_autorepeatoff(context->mlx);
	mlx_hook(context->window.ref, 2, 1L << 0, on_key_down, context);
	mlx_hook(context->window.ref, 3, 1L << 0, on_key_up, context);
	mlx_hook(context->window.ref, 17, 0, on_destroy, NULL);
	mlx_loop(context->mlx);
}
