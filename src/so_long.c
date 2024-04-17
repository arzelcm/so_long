/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:58:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/17 18:19:14 by arcanava         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_context	context;

	if (argc != 2)
		custom_error("Incorrect arguments. Usage: ./so_long map.ber", &context);
	handle_map(argv, &context);
	init_mlx(&context);
	use_map(&context.map, &context);
	terminate(&context);
	return (0);
}
