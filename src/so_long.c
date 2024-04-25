/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:58:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/04/25 12:09:14 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "mlx.h"
#include "map_parser.h"
#include "libft.h"

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
	handle_map(argv, &context.map);
	init_mlx(&context);
	use_map(&context.map, &context);
	return (EXIT_FAILURE);
}
