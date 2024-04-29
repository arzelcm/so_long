/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 11:39:11 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/29 18:11:20 by arcanava         ###   ########.fr       */
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

void	init_texture(t_texture *texture, char *img_path, void *mlx)
{
	texture->x_size = 0;
	texture->y_size = 0;
	texture->img = mlx_xpm_file_to_image(mlx, img_path,
			&texture->x_size, &texture->y_size);
}

void	set_window(t_texture *wall, t_texture *empty_space,
			t_map *map, t_context *context)
{
	if (wall->x_size != wall->y_size || wall->x_size != empty_space->x_size
		|| wall->y_size != empty_space->y_size)
		custom_error(
			"Texture images must be square and have exactly the same size!");
	context->window.title = context->map.name;
	context->window.width = empty_space->x_size * map->max_x;
	context->window.height = empty_space->y_size * map->max_y;
	if (context->window.width > WINDOW_MAX_WIDTH)
		context->window.width = ft_closest_multiple(WINDOW_MAX_WIDTH,
				wall->x_size);
	if (context->window.height > WINDOW_MAX_HEIGHT)
		context->window.height = ft_closest_multiple(WINDOW_MAX_HEIGHT,
				wall->y_size);
	context->window.ref = mlx_new_window(context->mlx, context->window.width,
			context->window.height, map->name);
}

void	put_moves(t_context *context)
{
	// unsigned long	num;
	// char	actual;

	// num = context->map.player.movements;
	// // while (num > 0)
	// // {
	// // 	actual = num % 10 + '0';
	// // 	ft_printf("nuuum: %c\n\n", actual);
	// // 	num /= 10;
	// // }
	printf("long: %ld, ltoa: %s\n\n", LONG_MIN, ft_ltoa(LONG_MIN));
	mlx_put_image_to_window(context->mlx, context->window.ref,
					context->map.enemy.img, context->window.width / 2, context->window.height / 2);
	mlx_string_put(context->mlx, context->window.ref, 0, context->window.width / 2, context->window.height / 2, ft_itoa(context->map.player.movements));
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
			else if (map->spaces[y + initial_y][x + initial_x] == ENEMY)
			{
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->empty_space.img, x * x_factr, y * y_factr);
				mlx_put_image_to_window(context->mlx, context->window.ref,
					map->enemy.img, x * x_factr, y * y_factr);
			}
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

	x_middle = context->window.width / 2 / map->wall.x_size;
	y_middle = context->window.height / 2 / map->wall.y_size;
	map->position.x = (long) map->player.pos.x - x_middle;
	map->position.y = (long) map->player.pos.y - y_middle;
}

void	move_map_view(long x_increment, long y_increment, t_context *context)
{
	context->map.position.x += x_increment;
	context->map.position.y += y_increment;
	parse_map(&context->map, context);
}

void	use_map(t_map *map, t_context *context)
{
	update_loading("Building map", 0);
	init_texture(&map->wall, "./assets/textures/waterfall.xpm", context->mlx);
	update_loading("Building map", 10);
	init_texture(&map->empty_space, "./assets/textures/empty-space.xpm",
		context->mlx);
	update_loading("Building map", 20);
	init_texture(&map->collectible, "./assets/sprites/fish.xpm", context->mlx);
	update_loading("Building map", 30);
	init_texture(&map->exit, "./assets/sprites/bed.xpm", context->mlx);
	update_loading("Building map", 50);
	init_texture(&map->player.texture, "./assets/sprites/nuu-i-pussi.xpm",
		context->mlx);
	init_texture(&map->enemy, "./assets/textures/wall.xpm",
		context->mlx);
	update_loading("Building map", 70);
	set_window(&map->wall, &map->empty_space, map, context);
	update_loading("Building map", 90);
	set_map_initial_pos(map, context);
	update_loading("Building map", 100);
	parse_map(map, context);
	ft_printf("\033[1A\033[2KMovements: %i\n", context->map.player.movements);
	set_actuator(context);
}
