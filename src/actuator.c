/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actuator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 13:53:52 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/30 22:25:58 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "mlx.h"
#include "libft.h"
#include "map_parser.h"
#include "actuator.h"
#include "background_worker.h"

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
