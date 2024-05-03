/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 13:40:00 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/03 13:46:45 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "map_parser.h"

void	set_camera_initial_pos(t_map *map, t_context *context)
{
	long	x_middle;
	long	y_middle;

	x_middle = context->window.width / 2 / map->empty_space.x_size;
	y_middle = context->window.height / 2 / map->empty_space.y_size;
	map->position.x = (long) map->player.pos.x - x_middle;
	map->position.y = (long) map->player.pos.y - y_middle;
}

void	move_camera(long x_increment, long y_increment, t_context *context)
{
	context->map.position.x += x_increment;
	context->map.position.y += y_increment;
	parse_map(&context->map, context);
}