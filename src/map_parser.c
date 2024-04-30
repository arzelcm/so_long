/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:39:11 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 21:44:43 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "actuator.h"
#include "loader.h"
#include "mlx.h"
#include "libft.h"
#include "window.h"
#include "so_long.h"
#include "limits.h"

void	set_window(t_map *map, t_context *context)
{
	if (map->wall->image.x_size != map->wall->image.y_size || map->wall->image.x_size != map->empty_space.x_size
		|| map->wall->image.y_size != map->empty_space.y_size)
		custom_error(
			"Texture images must be square and have exactly the same size!");
	context->window.title = context->map.name;
	context->window.width = map->empty_space.x_size * map->max_x;
	context->window.height = map->empty_space.y_size * map->max_y;
	if (context->window.width > WINDOW_MAX_WIDTH)
		context->window.width = ft_closest_multiple(WINDOW_MAX_WIDTH,
				map->wall->image.x_size);
	if (context->window.height > WINDOW_MAX_HEIGHT)
		context->window.height = ft_closest_multiple(WINDOW_MAX_HEIGHT,
				map->wall->image.y_size);
	context->window.ref = mlx_new_window(context->mlx, context->window.width,
			context->window.height, map->name);
}

void	put_moves(t_context *context)
{
	unsigned long	num;
	int				actual;
	int				digits;
	int				base_width;

	num = context->map.player.movements;
	digits = 0;
	while (num > 0)
	{
		digits++;
		num /= 10;
	}
	num = context->map.player.movements;
	base_width = context->window.width / 2 - context->font.numbers[0].x_size * digits / 2;
	while (num > 0)
	{
		actual = num % 10;
		mlx_put_image_to_window(context->mlx, context->window.ref,
				context->font.numbers[actual].ref,
				base_width + context->font.numbers[actual].x_size * (digits - 1),
				context->window.height - context->font.numbers[actual].y_size);
		digits--;
		num /= 10;
	}
}

void	parse_map(t_map *map, t_context *context)
{
	size_t		x;
	size_t		y;
	int			x_factr;
	int			y_factr;
	size_t		initial_y;
	size_t		initial_x;

	x_factr = map->empty_space.x_size;
	y_factr = map->empty_space.y_size;
	initial_y = ft_normalize(map->position.y, 0,
			map->max_y - context->window.height / y_factr);
	initial_x = ft_normalize(map->position.x, 0,
			map->max_x - context->window.width / x_factr);
	y = 0;
	mlx_clear_window(context->mlx, context->window.ref);
	while (y < map->max_y && y < (size_t) context->window.height / y_factr)
	{
		x = 0;
		while (x < map->max_x && x < (size_t) context->window.width / x_factr)
		{
			if (map->spaces[y + initial_y][x + initial_x] == WALL)
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->wall->image.ref, x * x_factr, y * y_factr);
			else
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->empty_space.ref, x * x_factr, y * y_factr);
			if (map->spaces[y + initial_y][x + initial_x] == EXIT)
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->exit.ref, x * x_factr, y * y_factr);
			else if (map->spaces[y + initial_y][x + initial_x] == COLLECTIBLE)
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->collectible.ref, x * x_factr, y * y_factr);
			else if (map->spaces[y + initial_y][x + initial_x] == PLAYER)
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->player.texture.ref, x * x_factr, y * y_factr);
			else if (map->spaces[y + initial_y][x + initial_x] == ENEMY)
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->enemy.ref, x * x_factr, y * y_factr);
			x++;
		}
		y++;
	}
	put_moves(context);
}

void	set_map_initial_pos(t_map *map, t_context *context)
{
	long	x_middle;
	long	y_middle;

	x_middle = context->window.width / 2 / map->empty_space.x_size;
	y_middle = context->window.height / 2 / map->empty_space.y_size;
	map->position.x = (long) map->player.pos.x - x_middle;
	map->position.y = (long) map->player.pos.y - y_middle;
}

void	move_map_view(long x_increment, long y_increment, t_context *context)
{
	context->map.position.x += x_increment;
	context->map.position.y += y_increment;
	parse_map(&context->map, context);
}

void	set_wall_sprite(t_context *context)
{
	context->map.wall = NULL;
	push_sprite(&context->map.wall, "./assets/sprites/waterfall1.xpm", context->mlx);
	push_sprite(&context->map.wall, "./assets/sprites/waterfall2.xpm", context->mlx);
	push_sprite(&context->map.wall, "./assets/sprites/waterfall3.xpm", context->mlx);
	push_sprite(&context->map.wall, "./assets/sprites/waterfall4.xpm", context->mlx);
}

void	use_map(t_map *map, t_context *context)
{
	update_loading("Building map", 0);
	set_wall_sprite(context);
	update_loading("Building map", 10);
	set_image(&map->empty_space, "./assets/textures/empty-space.xpm",
		context->mlx);
	update_loading("Building map", 20);
	set_image(&map->collectible, "./assets/sprites/fish.xpm", context->mlx);
	update_loading("Building map", 30);
	set_image(&map->exit, "./assets/sprites/bed.xpm", context->mlx);
	update_loading("Building map", 50);
	set_image(&map->player.texture, "./assets/sprites/nuu-i-pussi.xpm",
		context->mlx);
	set_image(&map->enemy, "./assets/textures/wall.xpm",
		context->mlx);
	update_loading("Building map", 70);
	set_window(map, context);
	update_loading("Building map", 90);
	set_map_initial_pos(map, context);
	update_loading("Building map", 100);
	parse_map(map, context);
	ft_printf("\033[1A\033[2KMovements: %l\n", context->map.player.movements);
	set_actuator(context);
}
