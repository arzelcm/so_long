/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:58:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/27 17:26:13 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "mlx.h"
#include "map_parser.h"
#include "libft.h"
#include "window.h"
#include <signal.h>

void	terminate(int sig)
{
	ft_printf("%i\n\033[?25h\n", sig);
	exit(EXIT_FAILURE);
}

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
	signal(SIGINT, terminate);
	init_context(&context);
	handle_map(argv, &context.map);
	init_mlx(&context);
	use_map(&context.map, &context);
	return (EXIT_FAILURE);
}
