/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actuator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:53:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/26 21:19:12 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include "libft.h"
#include "map_parser.h"

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
	update_player_movement(key, &context->map.player, 0);
	return (1);
}

void	check_player_movement(t_context *context)
{
	t_position pos;

	if (context->map.player.movement_iterations++ % 700 != 0)
		return ;
	pos = context->map.player.pos;
	if (context->map.player.moving_up)
		move_player(&context->map.player, 0, -1, &context->map);
	if (context->map.player.moving_down)
		move_player(&context->map.player, 0, 1, &context->map);
	if (context->map.player.moving_left)
		move_player(&context->map.player, -1, 0, &context->map);
	if (context->map.player.moving_right)
		move_player(&context->map.player, 1, 0, &context->map);
	if (pos.y != context->map.player.pos.y || pos.x != context->map.player.pos.x)
		move_map_position(context->map.player.pos.x - pos.x,
			context->map.player.pos.y - pos.y, context);
}

int background_loop(t_context *context)
{
	check_player_movement(context);
	context->window.loop_iter++;
	return (1);
}
