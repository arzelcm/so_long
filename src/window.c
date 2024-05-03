/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:11:17 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/03 13:31:14 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "window.h"
#include "map.h"
#include "so_long.h"
#include "utils.h"
#include "mlx.h"

void	init_window(t_window *window)
{
	window->height = 0;
	window->width = 0;
	window->loop_iter = 0;
	window->x_fact = 0;
	window->y_fact = 0;
	window->ref = NULL;
	window->title = NULL;
}

int	on_destroy(void)
{
	ft_printf("\033[?25h");
	exit(EXIT_SUCCESS);
}

void	set_window(t_window *window, t_map *map, void *mlx)
{
	if (map->wall->image.x_size != map->wall->image.y_size
		|| map->wall->image.x_size != map->empty_space.x_size
		|| map->wall->image.y_size != map->empty_space.y_size)
		custom_error(
			"Texture images must be square and have exactly the same size!");
	window->title = map->name;
	window->width = map->empty_space.x_size * map->max_x;
	window->height = map->empty_space.y_size * map->max_y;
	if (window->width > WINDOW_MAX_WIDTH)
		window->width = ft_closest_multiple(WINDOW_MAX_WIDTH,
				map->wall->image.x_size);
	if (window->height > WINDOW_MAX_HEIGHT)
		window->height = ft_closest_multiple(WINDOW_MAX_HEIGHT,
				map->wall->image.y_size);
	window->ref = mlx_new_window(mlx, window->width,
			window->height, map->name);
}
