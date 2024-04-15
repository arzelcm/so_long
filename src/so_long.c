/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:58:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/15 18:41:44 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "utils.h"
#include <fcntl.h>

// TODO: Refactor error management! Should have Error\n in every error!

void	terminate(t_context *context)
{
	terminate_map(&context->map);
}

void	init_mlx(t_context *context)
{
	context->mlx = mlx_init();
}

int	on_key_down(int key, t_context *context)
{
	if (key == ESC_KEYCODE)
	{
		mlx_destroy_window(context->mlx, context->window);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

void	open_map(t_map *map, t_context *context)
{
	void	*img;
	int		height;

	context->window = mlx_new_window(context->mlx, 1920, 1080, map->name);
	mlx_key_hook(context->window, on_key_down, context);
	height = 500;
	img = mlx_xpm_file_to_image(context->mlx, "./assets/sprites/Leafs2.xpm", &height, &height);
	mlx_put_image_to_window(context->mlx, context->window, img, 20, 20);
	mlx_loop(context->mlx);
}

int	main(int argc, char **argv)
{
	t_context	context;

	if (argc != 2)
		custom_error("Incorrect arguments. Usage: ./so_long map.ber", &context);
	handle_map(argv, &context);
	init_mlx(&context);
	open_map(&context.map, &context);
	terminate(&context);
	return (0);
}
