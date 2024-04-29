/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actuator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:53:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/29 12:18:56 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include "libft.h"
#include "map_parser.h"
#include "actuator.h"

void	check_player_movement(t_context *context)
{
	t_position	pos;

	if (context->map.player.movement_iterations++
		% ft_normalize(KEY_ITERATION_DELAY - context->map.player.acceleration,
			2, KEY_ITERATION_DELAY) != 0)
		return ;
	pos = context->map.player.pos;
	if (context->map.player.moving_up && !context->map.player.moving_down)
		move_player(&context->map.player, 0, -1, &context->map);
	if (context->map.player.moving_down && !context->map.player.moving_up)
		move_player(&context->map.player, 0, 1, &context->map);
	if (context->map.player.moving_left && !context->map.player.moving_right)
		move_player(&context->map.player, -1, 0, &context->map);
	if (context->map.player.moving_right && !context->map.player.moving_left)
		move_player(&context->map.player, 1, 0, &context->map);
	if (pos.y != context->map.player.pos.y || pos.x != context->map.player.pos.x)
		move_map_view(context->map.player.pos.x - pos.x,
			context->map.player.pos.y - pos.y, context);
}

int	background_loop(t_context *context)
{
	check_player_movement(context);
	context->window.loop_iter++;
	return (1);
}

int	on_key_down(int key, t_context *context)
{
	if (key == ESC_KEYCODE)
	{
		mlx_destroy_window(context->mlx, context->window.ref);
		ft_printf("\033[?25h");
		exit(EXIT_SUCCESS);
	}
	update_player_movement(key, &context->map.player, 1);
	return (1);
}

int	on_key_up(int key, t_context *context)
{
	update_player_movement(key, &context->map.player, -1);
	return (1);
}

void	set_actuator(t_context *context)
{
	mlx_do_key_autorepeatoff(context->mlx);
	mlx_hook(context->window.ref, 2, 1L << 0, on_key_down, context);
	mlx_hook(context->window.ref, 3, 1L << 1, on_key_up, context);
	mlx_hook(context->window.ref, 17, 0, on_destroy, NULL);
	mlx_loop_hook(context->mlx, background_loop, context);
	mlx_loop(context->mlx);
}
