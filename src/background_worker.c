/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_worker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 22:20:02 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/03 13:46:02 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "background_worker.h"
#include "context.h"
#include "libft.h"
#include "map_parser.h"
#include "camera.h"

void	check_player_movement(t_context *context)
{
	t_position	pos;

	if (context->map.player.movement_iterations++
		% ft_normalize(KEY_ITERATION_DELAY - context->map.player.acceleration,
			1, KEY_ITERATION_DELAY) != 0)
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
	if (pos.y != context->map.player.pos.y
		|| pos.x != context->map.player.pos.x)
		move_camera(context->map.player.pos.x - pos.x,
			context->map.player.pos.y - pos.y, context);
}

void	update_sprites(t_context *context)
{
	if (context->window.loop_iter % 5500)
		return ;
	context->map.wall = context->map.wall->next;
	parse_map(&context->map, context);
}

int	background_loop(t_context *context)
{
	check_player_movement(context);
	update_sprites(context);
	context->window.loop_iter++;
	return (1);
}
