/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:58:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/26 21:08:19 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "mlx.h"
#include "map_parser.h"
#include "libft.h"
#include "window.h"

void	init_context(t_context *context)
{
	context->mlx = NULL;
	init_window(&context->window);
}

void	init_mlx(t_context *context)
{
	context->mlx = mlx_init();
}

int	main(int argc, char **argv)
{
	t_context	context;

	if (argc != 2)
		custom_error("Incorrect arguments. Usage: ./so_long map.ber");
	ft_printf("\033[?25l\n");
	init_context(&context);
	handle_map(argv, &context.map);
	init_mlx(&context);
	use_map(&context.map, &context);
	return (EXIT_FAILURE);
}
