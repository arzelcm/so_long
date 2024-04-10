/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:58:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/10 22:07:33 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"
#include "utils.h"

int	main(int argc, char **argv)
{
	t_context	context;
	t_map		map;

	if (argc != 2)
		custom_error("Incorrect arguments. Usage: ./so_long map.ber", &context);
	handle_map(argc, argv, &map, &context);
	// context.mlx = mlx_init();
	// context.window = mlx_new_window(context.mlx, 1920, 1080, "Hello world!");
	// mlx_loop(context.mlx);
	return (0);
}
