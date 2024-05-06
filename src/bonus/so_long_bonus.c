/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arcanava <arcanava@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 12:58:55 by arcanava          #+#    #+#             */
/*   Updated: 2024/05/06 17:06:27 by arcanava         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"
#include "map_parser.h"
#include "libft.h"
#include "window.h"
#include "context.h"
#include "font.h"
#include <signal.h>

void	terminate(int sig)
{
	ft_printf("%i\n\033[?25h\n", sig);
	exit(EXIT_FAILURE);
}

int	main(int argc, char **argv)
{
	t_context	context;

	if (argc != 2)
		custom_error("Incorrect arguments. Usage: ./so_long map.ber");
	ft_printf("\033[?25l\n");
	signal(SIGINT, terminate);
	init_context(&context);
	set_map(argv[1], &context.map);
	use_map(&context.map, &context);
	return (EXIT_FAILURE);
}
