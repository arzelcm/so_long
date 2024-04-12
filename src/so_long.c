/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:58:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/12 19:05:07 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "utils.h"

void	terminate(t_context *context)
{
	terminate_map(&context->map);
}

int	main(int argc, char **argv)
{
	t_context	context;

	if (argc != 2)
		custom_error("Incorrect arguments. Usage: ./so_long map.ber", &context);
	handle_map(argv, &context);
	// context.mlx = mlx_init();
	// context.window = mlx_new_window(context.mlx, 1920, 1080, "Hello world!");
	// mlx_loop(context.mlx);
	terminate(&context);
	return (0);
}
